// -------------------------------------------------------------------------------------------------
//  Copyright (C) 2015-2024 Nautech Systems Pty Ltd. All rights reserved.
//  https://nautechsystems.io
//
//  Licensed under the GNU Lesser General Public License Version 3.0 (the "License");
//  You may not use this file except in compliance with the License.
//  You may obtain a copy of the License at https://www.gnu.org/licenses/lgpl-3.0.en.html
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// -------------------------------------------------------------------------------------------------

use std::collections::HashMap;

use anyhow::{bail, Result};
use indexmap::IndexMap;
use nautilus_model::identifiers::{instrument_id::InstrumentId, symbol::Symbol, venue::Venue};
use ustr::Ustr;

use super::types::PublisherId;

pub fn decode_nautilus_instrument_id(
    record: &dbn::RecordRef,
    publisher_id: PublisherId,
    metadata: &dbn::Metadata,
    publisher_venue_map: &IndexMap<PublisherId, Venue>,
    glbx_exchange_map: &HashMap<Symbol, Venue>,
) -> Result<InstrumentId> {
    let (instrument_id, nanoseconds) = if let Some(msg) = record.get::<dbn::MboMsg>() {
        (msg.hd.instrument_id, msg.ts_recv)
    } else if let Some(msg) = record.get::<dbn::TradeMsg>() {
        (msg.hd.instrument_id, msg.ts_recv)
    } else if let Some(msg) = record.get::<dbn::Mbp1Msg>() {
        (msg.hd.instrument_id, msg.ts_recv)
    } else if let Some(msg) = record.get::<dbn::Mbp10Msg>() {
        (msg.hd.instrument_id, msg.ts_recv)
    } else if let Some(msg) = record.get::<dbn::OhlcvMsg>() {
        (msg.hd.instrument_id, msg.hd.ts_event)
    } else {
        bail!("DBN message type is not currently supported")
    };

    let duration = time::Duration::nanoseconds(nanoseconds as i64);
    let datetime = time::OffsetDateTime::UNIX_EPOCH
        .checked_add(duration)
        .unwrap();
    let date = datetime.date();
    let symbol_map = metadata.symbol_map_for_date(date)?;
    let raw_symbol = symbol_map
        .get(instrument_id)
        .expect("No raw symbol found for {instrument_id}");

    let symbol = Symbol {
        value: Ustr::from(raw_symbol),
    };

    let venue = match glbx_exchange_map.get(&symbol) {
        Some(venue) => venue,
        None => publisher_venue_map
            .get(&publisher_id)
            .unwrap_or_else(|| panic!("No venue found for `publisher_id` {publisher_id}")),
    };

    Ok(InstrumentId::new(symbol, *venue))
}
