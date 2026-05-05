$version: "2"
namespace com.firebolt.wifi

service WifiService {
    version: "1.0"
    operations: [scan, connect, disconnect, wps]
}

operation scan {
    input: ScanInput
    output: ScanOutput
}

structure ScanInput {
    timeout: Timeout
}

structure ScanOutput {
    @required
    value: AccessPointList
}

operation connect {
    input: ConnectInput
    output: ConnectOutput
}

structure ConnectInput {
    passphrase: String
    security: WifiSecurityMode
    ssid: String
}

structure ConnectOutput {
    @required
    value: AccessPoint
}

operation disconnect {
    input: DisconnectInput
    output: DisconnectOutput
}

structure DisconnectInput {
}

structure DisconnectOutput {}

operation wps {
    input: WpsInput
    output: WpsOutput
}

structure WpsInput {
    security: WPSSecurityPin
}

structure WpsOutput {
    @required
    value: AccessPoint
}

structure AccessPoint {
    frequency: WifiFrequency
    securityMode: WifiSecurityMode
    signalStrength: WifiSignalStrength
    ssid: String
}

structure AccessPointList {
    list: AccessPointList
}

// TODO: alias Timeout = Integer (Smithy has no direct alias — use a newtype structure or inline the target)

enum WPSSecurityPin {
    MANUFACTURER_PIN = "manufacturerPin"
    PIN = "pin"
    PUSH_BUTTON = "pushButton"
}

structure WifiConnectRequest {
    passphrase: String
    securityMode: String
    ssid: String
    timeout: String
}

// TODO: alias WifiFrequency = Double (Smithy has no direct alias — use a newtype structure or inline the target)

enum WifiSecurityMode {
    NONE = "none"
    WEP128 = "wep128"
    WEP64 = "wep64"
    WPA2_ENTERPRISE = "wpa2Enterprise"
    WPA2_ENTERPRISE_AES = "wpa2EnterpriseAes"
    WPA2_ENTERPRISE_TKIP = "wpa2EnterpriseTkip"
    WPA2_PSK = "wpa2Psk"
    WPA2_PSK_AES = "wpa2PskAes"
    WPA2_PSK_TKIP = "wpa2PskTkip"
    WPA3_PSK_AES = "wpa3PskAes"
    WPA3_SAE = "wpa3Sae"
    WPA_ENTERPRISE_AES = "wpaEnterpriseAes"
    WPA_ENTERPRISE_TKIP = "wpaEnterpriseTkip"
    WPA_PSK_AES = "wpaPskAes"
    WPA_PSK_TKIP = "wpaPskTkip"
}

// TODO: alias WifiSignalStrength = Integer (Smithy has no direct alias — use a newtype structure or inline the target)

list AccessPointList {
    member: AccessPoint
}
