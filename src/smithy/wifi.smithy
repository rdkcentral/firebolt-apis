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
    list: AccessPointItems
}

/// Defines the timeout in seconds. If the threshold for timeout is passed for
/// any operation without a result it will throw an error.
@range(min: 0)
integer Timeout

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

/// Wifi frequency in Ghz, for example 2.4 or 5.0.
@range(min: 0)
double WifiFrequency

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

/// Strength of wifi signal based on RSSI, expected range -255..0.
@range(min: -255, max: 0)
integer WifiSignalStrength

list AccessPointItems {
    member: AccessPoint
}
