//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
#include "mvrxchange_message.h"
#include "XmlFileHelper.h"
#include "json.h"

using namespace MVRxchangeNetwork;

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}


MVRxchangePacket::MVRxchangePacket()
{
    fFlag       = kMVR_Package_Flag;
    fNumber     = 0;
    fCount      = 0;
    fType       = 0;
    fBodyLength = 0;
    fData       = std::make_shared<MVRxchangeDynamicBuffer>();
    fData->GrowTo(30 * 1024 * 1024);
}

MVRxchangePacket::MVRxchangePacket(const MVRxchangePacket& ref)
{
    fBodyLength = ref.fBodyLength;
    fData       = ref.fData;
    fFlag       = ref.fFlag; 
    fVersion    = ref.fVersion;
    fNumber     = ref.fNumber;
    fCount      = ref.fCount;
    fType       = ref.fType;
}


MVRxchangePacket::~MVRxchangePacket()
{
}

const char* MVRxchangePacket::GetData() const
{
    return fData->GetData();
}

char* MVRxchangePacket::GetData()
{
    return fData->GetData();
}

size_t MVRxchangePacket::GetLength() const
{
    return total_header_length + fBodyLength;
}

const char* MVRxchangePacket::GetBody() const
{
    return fData->GetData() + total_header_length;
}

char* MVRxchangePacket::GetBody()
{
    return fData->GetData() + total_header_length;
}

size_t MVRxchangePacket::GetBodyLength() const
{
    return fBodyLength;
}

void MVRxchangePacket::SetBody(size_t length, char* buffer)
{
    fBodyLength = length;
    fData->GrowTo(total_header_length + length);
    memcpy(GetBody(), buffer, length);
}

bool MVRxchangePacket::DecodeHeader()
{
    memcpy(&fFlag, fData->GetData(), header_flag);
    fFlag = swap_endian(fFlag);
    
    if (fFlag != kMVR_Package_Flag) { return false; }



    memcpy(&fVersion,    GetData() + header_flag, header_version);
    memcpy(&fNumber,     GetData() + header_flag + header_version, header_number);
    memcpy(&fCount,      GetData() + header_flag + header_version + header_number, header_count);
    memcpy(&fType,       GetData() + header_flag + header_version + header_number + header_count, header_type);
    memcpy(&fBodyLength, GetData() + header_flag + header_version + header_number + header_count + header_type, header_payload_length);
    
    fVersion = swap_endian(fVersion);
    fNumber = swap_endian(fNumber);
    fCount = swap_endian(fCount);
    fType= swap_endian(fType);
    fBodyLength = swap_endian(fBodyLength);

    // Prepare Buffer
    fData->GrowTo(fBodyLength);

    return true;
}

void MVRxchangePacket::EncodeHeader()
{
    fFlag = swap_endian(fFlag);
    fVersion = swap_endian(fVersion);
    fNumber = swap_endian(fNumber);
    fCount = swap_endian(fCount);
    fType = swap_endian(fType);
    fBodyLength = swap_endian(fBodyLength);
    
    memcpy(GetData(),                                                                               &fFlag,                 header_flag);
    memcpy(GetData() + header_flag,                                                                 &fVersion,              header_version);
    memcpy(GetData() + header_flag + header_version,                                                &fNumber,               header_number);
    memcpy(GetData() + header_flag + header_version + header_number,                                &fCount,                header_count);
    memcpy(GetData() + header_flag + header_version + header_number + header_count,                 &fType,                 header_type);
    memcpy(GetData() + header_flag + header_version + header_number + header_count + header_type,   &fBodyLength,           header_payload_length);


    fFlag = swap_endian(fFlag);
    fVersion = swap_endian(fVersion);
    fNumber = swap_endian(fNumber);
    fCount = swap_endian(fCount);
    fType = swap_endian(fType);
    fBodyLength = swap_endian(fBodyLength);
}

// ----- MVR_COMMIT (de)serialization ------
// Serialization here is split out, as the Commit Message Type is reused for File Arrays

void MVR_COMMIT_ToJson(const IMVRxchangeService::MVR_COMMIT_MESSAGE& msg, nlohmann::json& payload)
{
    payload["Type"]             = "MVR_COMMIT";
    payload["Comment"]          = msg.Comment;
    payload["FileSize"]         = msg.FileSize;
    payload["FileUUID"]         = SceneData::GdtfConverter::ConvertUUID(VWUUID(msg.FileUUID.a, msg.FileUUID.b, msg.FileUUID.c, msg.FileUUID.d)).GetStdString();
    payload["StationUUID"]      = SceneData::GdtfConverter::ConvertUUID(VWUUID(msg.StationUUID.a, msg.StationUUID.b, msg.StationUUID.c, msg.StationUUID.d)).GetStdString();
    payload["verMinor"]         = msg.VersionMinor;
    payload["verMajor"]         = msg.VersionMajor;
    payload["ForStationsUUID"]  = nlohmann::json::array();
    // TODO
    for(const auto& e : msg.ForStationsUUID)
    {
        payload["ForStationsUUID"].push_back(SceneData::GdtfConverter::ConvertUUID(VWUUID(e.a, e.b, e.c, e.d)).GetStdString());
    }

}

void MVR_COMMIT_FromJson(const nlohmann::json& payload, IMVRxchangeService::MVR_COMMIT_MESSAGE& in)
{
    strcpy(in.Comment, payload["Comment"].get<std::string>().c_str());
    in.VersionMajor= payload["verMajor"];
    in.VersionMinor= payload["verMinor"];
    in.FileSize= payload["FileSize"];

    SceneData::GdtfConverter::ConvertUUID(payload["FileUUID"].get<std::string>(), in.FileUUID);
    SceneData::GdtfConverter::ConvertUUID(payload["StationUUID"].get<std::string>(), in.StationUUID);

    in.ForStationsUUID.clear();
    // TODO
    for(const auto& e : payload["ForStationsUUID"])
    {
        in.ForStationsUUID.emplace_back();
        if(!SceneData::GdtfConverter::ConvertUUID(e.get<std::string>(), in.ForStationsUUID.back())){
            in.ForStationsUUID.pop_back();
        }
    }
}

// -----------------------------------------

void MVRxchangePacket::FromExternalMessage(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    nlohmann::json payload = nlohmann::json::object();

    switch (in.Type)
    {
    case IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN:
        payload["Type"]         = "MVR_JOIN";
        payload["Provider"]     = in.JOIN.Provider;
        payload["StationName"]  = in.JOIN.StationName;
        payload["StationUUID"]  = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.JOIN.StationUUID.a, in.JOIN.StationUUID.b, in.JOIN.StationUUID.c, in.JOIN.StationUUID.d)).GetStdString();
        payload["verMajor"]     = in.JOIN.VersionMajor;
        payload["verMinor"]     = in.JOIN.VersionMinor;

        payload["Files"] = nlohmann::json::array();
        for(auto& it : in.JOIN.Files)
        {
            nlohmann::json obj = nlohmann::json::object();
            MVR_COMMIT_ToJson(it, obj);
            payload["Files"].push_back(obj);
        }

        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN_RET:
        payload["OK"]           = in.RetIsOK;
        payload["Message"]      = in.RetError;
        payload["Type"]         = "MVR_JOIN_RET";
        payload["Provider"]     = in.JOIN.Provider;
        payload["StationName"]  = in.JOIN.StationName;
        payload["StationUUID"]  = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.JOIN.StationUUID.a, in.JOIN.StationUUID.b, in.JOIN.StationUUID.c, in.JOIN.StationUUID.d)).GetStdString();
        payload["verMajor"]     = in.JOIN.VersionMajor;
        payload["verMinor"]     = in.JOIN.VersionMinor;

        payload["Files"] = nlohmann::json::array();
        for(auto& it : in.JOIN.Files)
        {
            nlohmann::json obj = nlohmann::json::object();
            MVR_COMMIT_ToJson(it, obj);
            payload["Files"].push_back(obj);
        }

        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_LEAVE:
        payload["Type"]         = "MVR_LEAVE";
        payload["FromStationUUID"]  = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.LEAVE.FromStationUUID.a, in.LEAVE.FromStationUUID.b, in.LEAVE.FromStationUUID.c, in.LEAVE.FromStationUUID.d)).GetStdString();
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_LEAVE_RET:
        payload["Type"]         = "MVR_LEAVE_RET";
        payload["OK"]           = in.RetIsOK;
        payload["Message"]      = in.RetError;
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT:
        MVR_COMMIT_ToJson(in.COMMIT, payload);
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT_RET:
        payload["OK"]               = in.RetIsOK;
        payload["Message"]          = in.RetError;
        payload["Type"]             = "MVR_COMMIT_RET";
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST:
        payload["Type"]             = "MVR_REQUEST";
        payload["FileUUID"]         = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.REQUEST.FileUUID.a, in.REQUEST.FileUUID.b, in.REQUEST.FileUUID.c, in.REQUEST.FileUUID.d)).GetStdString();
        payload["FromStationUUID"]  = nlohmann::json::array();
        for(const auto& e : in.REQUEST.FromStationUUID)
        {
            payload["FromStationUUID"].push_back(SceneData::GdtfConverter::ConvertUUID(VWUUID(e.a, e.b, e.c, e.d)).GetStdString());
        }
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET:
        payload["Type"]             = "MVR_REQUEST_RET";
        payload["OK"]               = in.RetIsOK;
        payload["Message"]          = in.RetError;

        break;
    default:
        break;
    }


    fFlag       = kMVR_Package_Flag;
    fNumber     = 0;
    fCount      = 1;

    if(in.Type == IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET && in.RetIsOK)
    {
        if(in.BufferToFile == nullptr)
        {
            IFileIdentifierPtr file (IID_FileIdentifier);
            file->Set(in.PathToFile.fBuffer);

            Uint64 size = 0;
            IRawOSFilePtr rawFile (IID_RawOSFile);
            rawFile->Open(file, true, false,true, false);
            rawFile->GetFileSize(fBodyLength);
            fData->GrowTo(fBodyLength + total_header_length);
            rawFile->Read(0, fBodyLength, GetBody());
            rawFile->Close();
        }
        else
        {
            fBodyLength = in.BufferToFileLength;
            fData->GrowTo(fBodyLength + total_header_length);
            memcpy(GetBody(), in.BufferToFile, fBodyLength);
        }

        fType       = kMVR_Package_BUFFER_TYPE;
    }
    else
    {
        std::string s = payload.dump();
        fBodyLength = s.size();
        fType       = kMVR_Package_JSON_TYPE;

        fData->GrowTo(fBodyLength + total_header_length);
        memcpy(GetBody(), s.data(), fBodyLength);
    }

    EncodeHeader();
}

void MVRxchangePacket::ToExternalMessage(VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    if(fType == kMVR_Package_JSON_TYPE && fBodyLength > 0)
    {
        nlohmann::json payload = nlohmann::json::parse(this->GetBody(),this->GetBody() + fBodyLength,  nullptr, false, true);
        
        if(payload.type() ==  nlohmann::json::value_t::object)
        {
            if(payload["Type"] == "MVR_JOIN")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN;
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
                strcpy(in.JOIN.Provider, payload["Provider"].get<std::string>().c_str());
                strcpy(in.JOIN.StationName, payload["StationName"].get<std::string>().c_str());
                SceneData::GdtfConverter::ConvertUUID(payload["StationUUID"].get<std::string>(), in.JOIN.StationUUID);

                in.JOIN.Files.clear();
                for(auto& it : payload["Files"])
                {
                    in.JOIN.Files.emplace_back();
                    MVR_COMMIT_FromJson(it, in.JOIN.Files.back());
                }
            }
            else if(payload["Type"] == "MVR_JOIN_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN_RET;
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
                strcpy(in.JOIN.Provider, payload["Provider"].get<std::string>().c_str());
                strcpy(in.JOIN.StationName, payload["StationName"].get<std::string>().c_str());
                SceneData::GdtfConverter::ConvertUUID(payload["StationUUID"].get<std::string>(), in.JOIN.StationUUID);

                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());

                in.JOIN.Files.clear();
                for(auto& it : payload["Files"])
                {
                    in.JOIN.Files.emplace_back();
                    MVR_COMMIT_FromJson(it, in.JOIN.Files.back());
                }
            }
            else if(payload["Type"] == "MVR_COMMIT")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT;
                MVR_COMMIT_FromJson(payload, in.COMMIT);
            }
            else if(payload["Type"] == "MVR_COMMIT_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT_RET;
                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());
            }
            else if(payload["Type"] == "MVR_REQUEST")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST;
                SceneData::GdtfConverter::ConvertUUID(payload["FileUUID"].get<std::string>(), in.REQUEST.FileUUID);

                in.REQUEST.FromStationUUID.clear();
                // TODO
                for(const auto& e : payload["FromStationsUUID"])
                {
                    in.REQUEST.FromStationUUID.emplace_back();
                    if(!SceneData::GdtfConverter::ConvertUUID(e.get<std::string>(), in.REQUEST.FromStationUUID.back())){
                        in.REQUEST.FromStationUUID.pop_back();
                    }
                }
            }
            else if(payload["Type"] == "MVR_REQUEST_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET;
                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());
            }
            else if(payload["Type"] == "MVR_LEAVE")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_LEAVE;
                SceneData::GdtfConverter::ConvertUUID(payload["FromStationUUID"].get<std::string>(), in.LEAVE.FromStationUUID);
            }
            else if(payload["Type"] == "MVR_LEAVE_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_LEAVE_RET;
                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());
            }
        }
    }
    else if(fType == kMVR_Package_BUFFER_TYPE && fBodyLength > 0)
    {
        in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET;
        in.BufferToFileLength = fBodyLength;
        in.BufferToFile = new char[fBodyLength];
        memcpy(in.BufferToFile, GetBody(), fBodyLength);
    }
}
