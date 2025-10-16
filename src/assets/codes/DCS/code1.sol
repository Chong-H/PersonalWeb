pragma solidity ^0.4.25;

contract TransactionRecord {

    struct Trade {
        uint256 transactionId;
        uint256 collectibleId;
        uint256 buyerId;
        uint256 sellerId;
        string transactionDate;
    }

    mapping(uint256 => Trade) public trades;

    event TradeRecorded(
        uint256 transactionId,
        uint256 collectibleId,
        uint256 buyerId,
        uint256 sellerId,
        string transactionDate
    );

    function recordTrade(
        uint256 transactionId,
        uint256 collectibleId,
        uint256 buyerId,
        uint256 sellerId,
        string transactionDate
    ) public {
        require(trades[transactionId].transactionId == 0); // 确保不重复记录

        trades[transactionId] = Trade(
            transactionId,
            collectibleId,
            buyerId,
            sellerId,
            transactionDate
        );

        emit TradeRecorded(transactionId, collectibleId, buyerId, sellerId, transactionDate);
    }

    function getTrade(uint256 transactionId) public view returns (
        uint256, uint256, uint256, uint256, string
    ) {
        Trade memory t = trades[transactionId];
        return (
            t.transactionId,
            t.collectibleId,
            t.buyerId,
            t.sellerId,
            t.transactionDate
        );
    }
}