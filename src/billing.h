#pragma once
#include "EventDispatcher.h"
#include "Event.h"
#include "json/json.h"
#include <string>

namespace oxygine
{
    namespace billing
    {
        class PurchasedEvent : public Event
        {
        public:
            enum { EVENT = sysEventID('b', 'p', 'r') };
            PurchasedEvent(const Json::Value& data_, const Json::Value& signature_) : Event(EVENT), data(data_), signature(signature_) {}

            Json::Value data;
            Json::Value signature;
        };

        class ParsePurchasedData
        {
        public:
            ParsePurchasedData(const PurchasedEvent* event);

            std::string productID;
        };

        class DetailsEvent : public Event
        {
        public:
            enum { EVENT = sysEventID('b', 'd', 't') };
            DetailsEvent(const Json::Value& data_) : Event(EVENT), data(data_) {}

            Json::Value data;


            /*
            //android
            [
                {
                    "description" : "A little pack of coins.",
                        "price" : "30,00 ?",
                        "price_amount_micros" : 30000000,
                        "price_currency_code" : "RUB",
                        "productId" : "com.package.game.pack1",
                        "title" : "Coins pack 1",
                        "type" : "inapp"
                },
                {
                    "description" : "A middle pack of coins.",
                    "price" : "60,00 ?",
                    "price_amount_micros" : 60000000,
                    "price_currency_code" : "RUB",
                    "productId" : "com.package.game.pack2",
                    "title" : "Coins pack 2",
                    "type" : "inapp"
                },
            ]
            */
        };

        class ParsedDetailsData
        {
        public:
            ParsedDetailsData(const DetailsEvent* event);

            class Item
            {
            public:
                Item() : price_amount_micros(0) {}

                std::string     productId;
                std::string     description;
                std::string     price;
                int64           price_amount_micros;
                std::string     price_currency_code;
                std::string     title;
                std::string     type;
            };

            std::vector<Item> items;
        };

        spEventDispatcher dispatcher();

        /**initializes oxygine-billing module*/
        void init();

        /**free oxygine-billing module*/
        void free();

        void purchase(const std::string& id, const std::string& payload);
        
        
        void consume(const std::string& token);
        

        void requestPurchases();
        void requestDetails(const std::vector<std::string>& items);

        void simulatorSetDetails(const Json::Value& details);

        enum MarketType
        {
            ios,
            google,
            amazon
        };

        MarketType getMarketType();


        namespace internal
        {
            void purchased(const std::string&, const std::string&);
            //void detailed(const std::string&);
            void detailed(const Json::Value&);
        }
    }
}
