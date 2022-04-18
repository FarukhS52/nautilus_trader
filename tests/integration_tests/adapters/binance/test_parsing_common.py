# -------------------------------------------------------------------------------------------------
#  Copyright (C) 2015-2022 Nautech Systems Pty Ltd. All rights reserved.
#  https://nautechsystems.io
#
#  Licensed under the GNU Lesser General Public License Version 3.0 (the "License");
#  You may not use this file except in compliance with the License.
#  You may obtain a copy of the License at https://www.gnu.org/licenses/lgpl-3.0.en.html
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
# -------------------------------------------------------------------------------------------------

import pytest

from nautilus_trader.adapters.binance.spot.enums import BinanceSpotOrderType
from nautilus_trader.adapters.binance.spot.parsing.execution import parse_order_type
from nautilus_trader.model.enums import OrderType


class TestBinanceSpotParsing:
    @pytest.mark.parametrize(
        "order_type, expected",
        [
            [BinanceSpotOrderType.MARKET, OrderType.MARKET],
            [BinanceSpotOrderType.LIMIT, OrderType.LIMIT],
            [BinanceSpotOrderType.STOP, OrderType.STOP_MARKET],
            [BinanceSpotOrderType.STOP_LOSS, OrderType.STOP_MARKET],
            [BinanceSpotOrderType.TAKE_PROFIT, OrderType.LIMIT],
            [BinanceSpotOrderType.TAKE_PROFIT_LIMIT, OrderType.STOP_LIMIT],
        ],
    )
    def test_parse_order_type(self, order_type, expected):
        # Arrange, # Act
        result = parse_order_type(order_type)

        # Assert
        assert result == expected
