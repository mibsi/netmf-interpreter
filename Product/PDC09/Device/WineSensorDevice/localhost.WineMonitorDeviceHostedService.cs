//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     .NET Micro Framework MFSvcUtil.Exe
//     Runtime Version:2.0.00001.0001
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


using System;
using System.Text;
using System.Xml;
using Dpws.Device;
using Dpws.Device.Services;
using Ws.Services;
using Ws.Services.WsaAddressing;
using Ws.Services.Xml;

namespace localhost.WineMonitorDevice
{
    
    
    public class IWineMonitorRequest : DpwsHostedService
    {
        
        private IIWineMonitorRequest m_service = null;
        
        public IWineMonitorRequest(IIWineMonitorRequest service)
        {
            // Set the service implementation properties
            m_service = service;

            // Set base service properties
            ServiceNamespace = new WsXmlNamespace("iwi", "http://localhost/WineMonitorDevice/");
            ServiceID = "urn:uuid:fd81af52-459d-4d35-87dc-298a029f9e89";
            ServiceTypeName = "IWineMonitorRequest";

            // Add service types here
            ServiceOperations.Add(new WsServiceOperation("http://localhost/WineMonitorDevice", "RequestUpdate"));
            ServiceOperations.Add(new WsServiceOperation("http://localhost/WineMonitorDevice", "SetThresholds"));

            // Add event sources here
        }
        
        public virtual Byte[] RequestUpdate(WsWsaHeader header, XmlReader reader)
        {
            // Build request object
            RequestUpdateDataContractSerializer reqDcs;
            reqDcs = new RequestUpdateDataContractSerializer("RequestUpdate", "http://localhost/WineMonitorDevice/");
            RequestUpdate req;
            req = ((RequestUpdate)(reqDcs.ReadObject(reader)));

            // Create response object
            // Call service operation to process request and return response.
            RequestUpdateResponse resp;
            resp = m_service.RequestUpdate(req);

            // Create response header
            WsWsaHeader respHeader = new WsWsaHeader("http://localhost/WineMonitorDevice/IWineMonitorRequest/RequestUpdateResponse", header.MessageID, WsWellKnownUri.WsaAnonymousUri, null, null, null);

            // Create response serializer
            RequestUpdateResponseDataContractSerializer respDcs;
            respDcs = new RequestUpdateResponseDataContractSerializer("RequestUpdateResponse", "http://localhost/WineMonitorDevice/");

            // Build response message and return
            return SoapMessageBuilder.BuildSoapMessage(respHeader, respDcs, resp);
        }
        
        public virtual Byte[] SetThresholds(WsWsaHeader header, XmlReader reader)
        {
            // Build request object
            SetThresholdsDataContractSerializer reqDcs;
            reqDcs = new SetThresholdsDataContractSerializer("SetThresholds", "http://localhost/WineMonitorDevice/");
            SetThresholds req;
            req = ((SetThresholds)(reqDcs.ReadObject(reader)));

            // Create response object
            // Call service operation to process request and return response.
            SetThresholdsResponse resp;
            resp = m_service.SetThresholds(req);

            // Create response header
            WsWsaHeader respHeader = new WsWsaHeader("http://localhost/WineMonitorDevice/IWineMonitorRequest/SetThresholdsResponse", header.MessageID, WsWellKnownUri.WsaAnonymousUri, null, null, null);

            // Create response serializer
            SetThresholdsResponseDataContractSerializer respDcs;
            respDcs = new SetThresholdsResponseDataContractSerializer("SetThresholdsResponse", "http://localhost/WineMonitorDevice/");

            // Build response message and return
            return SoapMessageBuilder.BuildSoapMessage(respHeader, respDcs, resp);
        }
    }
}