#pragma once
#include "Handlers/OperationsBarData/OperationsBarData.h"
#include <nlohmann/json.hpp>
using nlohmann::json;

#include <stdexcept>
#include <regex>

// Created by VERB1807 on 3/29/2024.

//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Session data = nlohmann::json::parse(jsonString);



namespace quicktype {
    using nlohmann::json;

#ifndef NLOHMANN_UNTYPED_quicktype_HELPER
#define NLOHMANN_UNTYPED_quicktype_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
#endif

    class SubOperationOperation;

    class OperationElement;

    class SubOperationOperation {
    public:
        SubOperationOperation() = default;
        virtual ~SubOperationOperation() = default;

    private:
        std::string label;
        int64_t duration;
        std::vector<OperationElement> sub_operations;

    public:
        const std::string & get_label() const { return label; }
        std::string & get_mutable_label() { return label; }
        void set_label(const std::string & value) { this->label = value; }

        const int64_t & get_duration() const { return duration; }
        int64_t & get_mutable_duration() { return duration; }
        void set_duration(const int64_t & value) { this->duration = value; }

        const std::vector<OperationElement> & get_sub_operations() const { return sub_operations; }
        std::vector<OperationElement> & get_mutable_sub_operations() { return sub_operations; }
        void set_sub_operations(const std::vector<OperationElement> & value) { this->sub_operations = value; }
    };

    class OperationElement {
    public:
        OperationElement() = default;
        virtual ~OperationElement() = default;

    private:
        int64_t timestamp;
        SubOperationOperation operation;

    public:
        const int64_t & get_timestamp() const { return timestamp; }
        int64_t & get_mutable_timestamp() { return timestamp; }
        void set_timestamp(const int64_t & value) { this->timestamp = value; }

        const SubOperationOperation & get_operation() const { return operation; }
        SubOperationOperation & get_mutable_operation() { return operation; }
        void set_operation(const SubOperationOperation & value) { this->operation = value; }
    };

    class Session {
    public:
        Session() = default;
        virtual ~Session() = default;

    private:
        int64_t start_timestamp;
        int64_t end_timestamp;
        std::vector<OperationElement> operations;

    public:
        const int64_t & get_start_timestamp() const { return start_timestamp; }
        int64_t & get_mutable_start_timestamp() { return start_timestamp; }
        void set_start_timestamp(const int64_t & value) { this->start_timestamp = value; }

        const int64_t & get_end_timestamp() const { return end_timestamp; }
        int64_t & get_mutable_end_timestamp() { return end_timestamp; }
        void set_end_timestamp(const int64_t & value) { this->end_timestamp = value; }

        const std::vector<OperationElement> & get_operations() const { return operations; }
        std::vector<OperationElement> & get_mutable_operations() { return operations; }
        void set_operations(const std::vector<OperationElement> & value) { this->operations = value; }
    };
}

namespace quicktype {
    void from_json(const json & j, SubOperationOperation & x);
    void to_json(json & j, const SubOperationOperation & x);

    void from_json(const json & j, OperationElement & x);
    void to_json(json & j, const OperationElement & x);

    void from_json(const json & j, Session & x);
    void to_json(json & j, const Session & x);

    inline void from_json(const json & j, SubOperationOperation& x) {
        x.set_label(j.at("label").get<std::string>());
        x.set_duration(j.at("duration").get<int64_t>());
        x.set_sub_operations(j.at("sub_operations").get<std::vector<OperationElement>>());
    }

    inline void to_json(json & j, const SubOperationOperation & x) {
        j = json::object();
        j["label"] = x.get_label();
        j["duration"] = x.get_duration();
        j["sub_operations"] = x.get_sub_operations();
    }

    inline void from_json(const json & j, OperationElement& x) {
        x.set_timestamp(j.at("timestamp").get<int64_t>());
        x.set_operation(j.at("operation").get<SubOperationOperation>());
    }

    inline void to_json(json & j, const OperationElement & x) {
        j = json::object();
        j["timestamp"] = x.get_timestamp();
        j["operation"] = x.get_operation();
    }

    inline void from_json(const json & j, Session& x) {
        x.set_start_timestamp(j.at("start_timestamp").get<int64_t>());
        x.set_end_timestamp(j.at("end_timestamp").get<int64_t>());
        x.set_operations(j.at("operations").get<std::vector<OperationElement>>());
    }

    inline void to_json(json & j, const Session & x) {
        j = json::object();
        j["start_timestamp"] = x.get_start_timestamp();
        j["end_timestamp"] = x.get_end_timestamp();
        j["operations"] = x.get_operations();
    }
}


class DataHandler
{
public:
		static SessionStruct ParseData(json jsonData)
		{
            SessionStruct session;

            quicktype::Session data = jsonData;

            session.end_timestamp = data.get_end_timestamp();
            session.start_timestamp = data.get_start_timestamp();

            std::vector<OperationData> opData;

            for (auto op : data.get_operations()) {
                opData.push_back(GenerateOperationStruct(op, 0));
            }

            session.operations = opData;

			return session;
		};

        static OperationData GenerateOperationStruct(quicktype::OperationElement element, int64_t startTimeOffset)
        {
            OperationData data;

            element.get_operation();

            data.operationName = QString::fromStdString(element.get_operation().get_label());
            data.start = element.get_timestamp() + startTimeOffset;
            data.end = element.get_operation().get_duration() + element.get_timestamp();

            std::vector<OperationData> opData;

            int timeOffset = startTimeOffset;

            for (auto op : element.get_operation().get_sub_operations()) {
                opData.push_back(GenerateOperationStruct(op, timeOffset));
            }

            data.subData = opData;

            return data;
        }
};