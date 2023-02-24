export module Settings {
    type LogLevel = "WARN" | "INFO" | "DEBUG" | "ERROR"
    function setLogLevel(logLevel: LogLevel): void
    function getLogLevel(): LogLevel     
}

export module Log {
    function info(...args: any[]): void
    function debug(...args: any[]): void
    function error(...args: any[]): void
    function warn(...args: any[]): void
}

export module Events {
    function listen(...args: any[]): Promise<number>
    function once(...args: any[]): Promise<number>
    function clear(...args: any[]): boolean
}

export module Accessibility {
type VoiceGuidanceSettings = {
  enabled: boolean              // Whether or not voice guidance should be enabled by default
  speed: number                 // The speed at which voice guidance speech will be read back to the user
}
type ClosedCaptionsSettings = {
  enabled: boolean               // Whether or not closed-captions should be enabled by default
  styles: ClosedCaptionsStyles   // The default styles to use when displaying closed-captions
}
type ListenResponse = {
  event: string
  listening: boolean
}
type ClosedCaptionsStyles = {
  fontFamily?: string
  fontSize?: number
  fontColor?: string
  fontEdge?: string
  fontEdgeColor?: string
  fontOpacity?: number
  backgroundColor?: string
  backgroundOpacity?: number
  textAlign?: string
  textAlignVertical?: string
}
type FontFamily = string
type FontSize = number
type Color = string
type FontEdge = string
type Opacity = number
type HorizontalAlignment = string
type VerticalAlignment = string


type Event = 'closedCaptionsSettingsChanged' | 'voiceGuidanceSettingsChanged'

/**
 * Get the user's preferred closed-captions settings
 */
function closedCaptionsSettings(): Promise<ClosedCaptionsSettings>
/**
 * Get the user's preferred closed-captions settings
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function closedCaptionsSettings(subscriber: (closedCaptionsSettings: ClosedCaptionsSettings) => void): Promise<number>
/**
 * Get the user's preferred voice guidance settings
*
* @deprecated since version 0.6.0.
 */
function voiceGuidance(): Promise<VoiceGuidanceSettings>
/**
 * Get the user's preferred voice guidance settings
 */
function voiceGuidanceSettings(): Promise<VoiceGuidanceSettings>
/**
 * Get the user's preferred voice guidance settings
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function voiceGuidanceSettings(subscriber: (settings: VoiceGuidanceSettings) => void): Promise<number>


  /**
  * Listen to all Accessibility events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Accessibility event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Accessibility event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'closedCaptionsSettingsChanged', listener: (data: ClosedCaptionsSettings) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Accessibility event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'closedCaptionsSettingsChanged', listener: (data: ClosedCaptionsSettings) => void): Promise<number>


  /**
   * Clear all Accessibility listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Accessibility event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'voiceGuidanceSettingsChanged', listener: (data: VoiceGuidanceSettings) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Accessibility event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'voiceGuidanceSettingsChanged', listener: (data: VoiceGuidanceSettings) => void): Promise<number>


  /**
   * Clear all Accessibility listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Account {




/**
 * Get the platform back-office account identifier
 */
function id(): Promise<string>
/**
 * Gets a unique id for the current app & account
 */
function uid(): Promise<string>





}
export module Advertising {
type ListenResponse = {
  event: string
  listening: boolean
}
type AdPolicy = {
  skipRestriction?: SkipRestriction  // The advertisement skip restriction.
  limitAdTracking?: boolean
}
type AdConfigurationOptions = {
  coppa?: boolean                // Whether or not the app requires US COPPA compliance.
  environment?: 'prod' | 'test'  // Whether the app is running in a production or test mode.
  authenticationEntity?: string  // The authentication provider, when it is separate entity than the app provider, e.g. an MVPD.
}


type Event = 'policyChanged'
enum SkipRestriction {
    NONE = 'none',
    ADS_UNWATCHED = 'adsUnwatched',
    ADS_ALL = 'adsAll',
    ALL = 'all'
}

/**
 * Build configuration object for Ad Framework initialization
 *
 * @param {AdConfigurationOptions} options Configuration options
 */
function config(options: AdConfigurationOptions): Promise<object>
/**
 * Get the advertising privacy and playback policy
 */
function policy(): Promise<AdPolicy>
/**
 * Get the advertising privacy and playback policy
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function policy(subscriber: (adPolicy: AdPolicy) => void): Promise<number>
/**
 * Get the advertising ID
 */
function advertisingId(): Promise<object>
/**
 * Get the device advertising device attributes
 */
function deviceAttributes(): Promise<object>
/**
 * Get the App's Bundle ID
 */
function appBundleId(): Promise<string>


  /**
  * Listen to all Advertising events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Advertising event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Advertising event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'policyChanged', listener: (data: AdPolicy) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Advertising event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'policyChanged', listener: (data: AdPolicy) => void): Promise<number>


  /**
   * Clear all Advertising listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Authentication {



enum TokenType {
    PLATFORM = 'platform',
    DEVICE = 'device',
    DISTRIBUTOR = 'distributor'
}

/**
 * Get a specific `type` of authentication token
*
* @deprecated since version 0.9.0.
 *
 * @param {TokenType} type What type of token to get
 * @param {object} options Additional options for acquiring the token.
 */
function token(type: TokenType, options?: object): Promise<object>
/**
 * Get a device token scoped to the current app.
 */
function device(): Promise<string>
/**
 * Get a destributor session token.
 */
function session(): Promise<string>
/**
 * Get a root device token.
 */
function root(): Promise<string>





}
export module ClosedCaptions {
type ListenResponse = {
  event: string
  listening: boolean
}
type FontFamily = string
type FontSize = number
type Color = string
type FontEdge = string
type Opacity = number
type HorizontalAlignment = string
type VerticalAlignment = string


type Event = 'enabledChanged' | 'fontFamilyChanged' | 'fontSizeChanged' | 'fontColorChanged' | 'fontEdgeChanged' | 'fontEdgeColorChanged' | 'fontOpacityChanged' | 'backgroundColorChanged' | 'backgroundOpacityChanged' | 'textAlignChanged' | 'textAlignVerticalChanged'

/**
 * Whether or not closed-captions are enabled.
 */
function enabled(): Promise<boolean>
/**
 * Whether or not closed-captions are enabled.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function enabled(subscriber: (enabled: boolean) => void): Promise<number>
/**
 * Whether or not closed-captions are enabled.
 *
 * @param {boolean} value The new enabled value.
 */
function enabled(value: boolean): Promise<void>
/**
 * The prefered font family for displaying closed-captions.
 */
function fontFamily(): Promise<string>
/**
 * The prefered font family for displaying closed-captions.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontFamily(subscriber: (family: string) => void): Promise<number>
/**
 * The prefered font family for displaying closed-captions.
 *
 * @param {string} value The new fontFamily value.
 */
function fontFamily(value: string): Promise<void>
/**
 * The prefered font size for displaying closed-captions.
 */
function fontSize(): Promise<number>
/**
 * The prefered font size for displaying closed-captions.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontSize(subscriber: (size: number) => void): Promise<number>
/**
 * The prefered font size for displaying closed-captions.
 *
 * @param {number} value The new fontSize value.
 */
function fontSize(value: number): Promise<void>
/**
 * The prefered font color for displaying closed-captions.
 */
function fontColor(): Promise<string>
/**
 * The prefered font color for displaying closed-captions.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontColor(subscriber: (color: string) => void): Promise<number>
/**
 * The prefered font color for displaying closed-captions.
 *
 * @param {string} value The new fontColor value.
 */
function fontColor(value: string): Promise<void>
/**
 * The prefered font edge style for displaying closed-captions.
 */
function fontEdge(): Promise<string>
/**
 * The prefered font edge style for displaying closed-captions.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontEdge(subscriber: (edge: string) => void): Promise<number>
/**
 * The prefered font edge style for displaying closed-captions.
 *
 * @param {string} value The new fontEdge value.
 */
function fontEdge(value: string): Promise<void>
/**
 * The prefered font edge color for displaying closed-captions.
 */
function fontEdgeColor(): Promise<string>
/**
 * The prefered font edge color for displaying closed-captions.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontEdgeColor(subscriber: (color: string) => void): Promise<number>
/**
 * The prefered font edge color for displaying closed-captions.
 *
 * @param {string} value The new fontEdgeColor value.
 */
function fontEdgeColor(value: string): Promise<void>
/**
 * The prefered opacity for displaying closed-captions characters.
 */
function fontOpacity(): Promise<number>
/**
 * The prefered opacity for displaying closed-captions characters.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function fontOpacity(subscriber: (opacity: number) => void): Promise<number>
/**
 * The prefered opacity for displaying closed-captions characters.
 *
 * @param {number} value The new fontOpacity value.
 */
function fontOpacity(value: number): Promise<void>
/**
 * The prefered background color for displaying closed-captions, .
 */
function backgroundColor(): Promise<string>
/**
 * The prefered background color for displaying closed-captions, .
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function backgroundColor(subscriber: (color: string) => void): Promise<number>
/**
 * The prefered background color for displaying closed-captions, .
 *
 * @param {string} value The new backgroundColor value.
 */
function backgroundColor(value: string): Promise<void>
/**
 * The prefered opacity for displaying closed-captions backgrounds.
 */
function backgroundOpacity(): Promise<number>
/**
 * The prefered opacity for displaying closed-captions backgrounds.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function backgroundOpacity(subscriber: (opacity: number) => void): Promise<number>
/**
 * The prefered opacity for displaying closed-captions backgrounds.
 *
 * @param {number} value The new backgroundOpacity value.
 */
function backgroundOpacity(value: number): Promise<void>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 */
function textAlign(): Promise<string>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function textAlign(subscriber: (opacity: string) => void): Promise<number>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 *
 * @param {string} value The new textAlign value.
 */
function textAlign(value: string): Promise<void>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 */
function textAlignVertical(): Promise<string>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function textAlignVertical(subscriber: (opacity: string) => void): Promise<number>
/**
 * The prefered horizontal alignment for displaying closed-captions characters.
 *
 * @param {string} value The new textAlignVertical value.
 */
function textAlignVertical(value: string): Promise<void>


  /**
  * Listen to all ClosedCaptions events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any ClosedCaptions event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'enabledChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'enabledChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontFamilyChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontFamilyChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontSizeChanged', listener: (data: number) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontSizeChanged', listener: (data: number) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontColorChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontColorChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontEdgeChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontEdgeChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontEdgeColorChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontEdgeColorChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'fontOpacityChanged', listener: (data: number) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'fontOpacityChanged', listener: (data: number) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'backgroundColorChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'backgroundColorChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'backgroundOpacityChanged', listener: (data: number) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'backgroundOpacityChanged', listener: (data: number) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'textAlignChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'textAlignChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'textAlignVerticalChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific ClosedCaptions event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'textAlignVerticalChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all ClosedCaptions listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Device {
type SemanticVersion = {
  major: number
  minor: number
  patch: number
  readable: string
}
type ListenResponse = {
  event: string
  listening: boolean
}
type Resolution = [number, number]
type AudioProfiles = {
  [property: string]: boolean
}
type BooleanMap = {
  [property: string]: boolean
}


type Event = 'deviceNameChanged' | 'nameChanged' | 'hdcpChanged' | 'hdrChanged' | 'audioChanged' | 'screenResolutionChanged' | 'videoResolutionChanged' | 'networkChanged'
enum NetworkType {
    WIFI = 'wifi',
    ETHERNET = 'ethernet',
    HYBRID = 'hybrid'
}
enum NetworkState {
    CONNECTED = 'connected',
    DISCONNECTED = 'disconnected'
}
enum AudioProfile {
    STEREO = 'stereo',
    DOLBY_DIGITAL_5_1 = 'dolbyDigital5.1',
    DOLBY_DIGITAL_7_1 = 'dolbyDigital7.1',
    DOLBY_DIGITAL_5_1_PLUS = 'dolbyDigital5.1+',
    DOLBY_DIGITAL_7_1_PLUS = 'dolbyDigital7.1+',
    DOLBY_ATMOS = 'dolbyAtmos'
}

/**
 * Get the platform back-office device identifier
 */
function id(): Promise<string>
/**
 * Get the distributor ID for this device
 */
function distributor(): Promise<string>
/**
 * Get the platform ID for this device
 */
function platform(): Promise<string>
/**
 * Gets a unique id for the current app & device
 */
function uid(): Promise<string>
/**
 * Get the device type
 */
function type(): Promise<string>
/**
 * Get the device model
 */
function model(): Promise<string>
/**
 * Get the device sku
 */
function sku(): Promise<string>
/**
 * Get the device make
 */
function make(): Promise<string>
/**
 * Get the SDK, OS and other version info
 */
function version(): Promise<object>
/**
 * Get the supported HDCP profiles
 */
function hdcp(): Promise<object>
/**
 * Get the supported HDCP profiles
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function hdcp(subscriber: (supportedHdcpProfiles: object) => void): Promise<number>
/**
 * Get the supported HDR profiles
 */
function hdr(): Promise<object>
/**
 * Get the supported HDR profiles
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function hdr(subscriber: (supportedHdrProfiles: object) => void): Promise<number>
/**
 * Get the supported audio profiles
 */
function audio(): Promise<AudioProfiles>
/**
 * Get the supported audio profiles
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function audio(subscriber: (supportedAudioProfiles: AudioProfiles) => void): Promise<number>
/**
 * Get the current screen resolution
 */
function screenResolution(): Promise<[number, number]>
/**
 * Get the current screen resolution
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function screenResolution(subscriber: (screenResolution: [number, number]) => void): Promise<number>
/**
 * Get the current video resolution
 */
function videoResolution(): Promise<[number, number]>
/**
 * Get the current video resolution
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function videoResolution(subscriber: (videoResolution: [number, number]) => void): Promise<number>
/**
 * The human readable name of the device
 */
function name(): Promise<string>
/**
 * The human readable name of the device
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function name(subscriber: (value: string) => void): Promise<number>
/**
 * The human readable name of the device
 *
 * @param {string} value The new name value.
 */
function name(value: string): Promise<void>
/**
 * Get the current network status and type
 */
function network(): Promise<object>
/**
 * Get the current network status and type
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function network(subscriber: (networkInfo: object) => void): Promise<number>


  /**
  * Listen to all Device events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Device event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'deviceNameChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'deviceNameChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'nameChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'nameChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'hdcpChanged', listener: (data: object) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'hdcpChanged', listener: (data: object) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'hdrChanged', listener: (data: object) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'hdrChanged', listener: (data: object) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'audioChanged', listener: (data: AudioProfiles) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'audioChanged', listener: (data: AudioProfiles) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'screenResolutionChanged', listener: (data: [number, number]) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'screenResolutionChanged', listener: (data: [number, number]) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'videoResolutionChanged', listener: (data: [number, number]) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'videoResolutionChanged', listener: (data: [number, number]) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'networkChanged', listener: (data: object) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'networkChanged', listener: (data: object) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Discovery {
type ListenResponse = {
  event: string
  listening: boolean
}
type DiscoveryPolicy = {
  enableRecommendations: boolean    // Whether or not to the user has enabled history-based recommendations
  shareWatchHistory: boolean        // Whether or not the user has enabled app watch history data to be shared with the platform
  rememberWatchedPrograms: boolean  // Whether or not the user has enabled watch history
}
type EntityInfo = {
  identifiers: ContentIdentifiers   // The ContentIdentifiers object is how the app identifies an entity or asset to
  title: string                     // Title of the entity.
  entityType: "program"
  programType: ProgramType          // In the case of a program `entityType`, specifies the program type.
  synopsis?: string                 // Short description of the entity.
  seasonNumber?: number             // For TV seasons, the season number. For TV episodes, the season that the episode belongs to.
  episodeNumber?: number            // For TV episodes, the episode number.
  releaseDate?: string              // The date that the program or entity was released or first aired.
  contentRatings?: ContentRating[]  // A list of ContentRating objects, describing the entity's ratings in various rating schemes.
  waysToWatch?: WayToWatch[]        // An array of ways a user is might watch this entity, regardless of entitlements.
}
type WayToWatch = {
  identifiers: ContentIdentifiers       // The ContentIdentifiers object is how the app identifies an entity or asset to
  expires?: string                      // Time when the WayToWatch is no longer available.
  entitled?: boolean                    // Specify if the user is entitled to watch the entity.
  entitledExpires?: string              // Time when the entity is no longer entitled.
  offeringType?: OfferingType           // The offering type of the WayToWatch.
  hasAds?: boolean                      // True if the streamable asset contains ads.
  price?: number                        // For "buy" and "rent" WayToWatch, the price to buy or rent in the user's preferred currency.
  videoQuality?: 'SD' | 'HD' | 'UHD'[]  // List of the video qualities available via the WayToWatch.
  audioProfile?: AudioProfile[]         // List of the audio types available via the WayToWatch.
  audioLanguages?: string[]             // List of audio track languages available on the WayToWatch. The first is considered the primary language. Languages are expressed as ISO 639 1/2 codes.
  closedCaptions?: string[]             // List of languages for which closed captions are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  subtitles?: string[]                  // List of languages for which subtitles are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  audioDescriptions?: string[]          // List of languages for which audio descriptions (DVS) are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
}
type ContentRating = {
  scheme: 'CA-Movie' | 'CA-TV' | 'CA-Movie-Fr' | 'CA-TV-Fr' | 'US-Movie' | 'US-TV'  // The rating scheme.
  rating: string                                                                    // The content rating.
  advisories?: string[]                                                             // Optional list of subratings or content advisories.
}
type ContentIdentifiers = {
  assetId?: string           // Identifies a particular playable asset. For example, the HD version of a particular movie separate from the UHD version.
  entityId?: string          // Identifies an entity, such as a Movie, TV Series or TV Episode.
  seasonId?: string          // The TV Season for a TV Episode.
  seriesId?: string          // The TV Series for a TV Episode or TV Season.
  appContentData?: string    // App-specific content identifiers.
}
type FederatedRequest = {
  correlationId: string
}
type EntityInfoFederatedRequest = {
  correlationId: string
  parameters: EntityInfoParameters
}
type EntityInfoParameters = {
  entityId: string
  assetId?: string
}
type EntityInfoResult = {
  expires: string
  entity: EntityInfo
  related?: EntityInfo[]
}
type PurchasedContentFederatedRequest = {
  correlationId: string
  parameters: PurchasedContentParameters
}
type PurchasedContentParameters = {
  limit: number
  offeringType?: OfferingType        // The offering type of the WayToWatch.
  programType?: ProgramType          // In the case of a program `entityType`, specifies the program type.
}
type PurchasedContentResult = {
  expires: string
  totalCount: number
  entries: EntityInfo[]
}
type Availability = {
  type: 'channel-lineup' | 'program-lineup'
  id: string
  catalogId?: string
  startTime?: string
  endTime?: string
}
type ContentAccessIdentifiers = {
  availabilities?: Availability[]  // A list of identifiers that represent what content is discoverable for the subscriber. Excluding availabilities will cause no change to the availabilities that are stored for this subscriber. Providing an empty array will clear the subscriber's availabilities
  entitlements?: Entitlement[]     // A list of identifiers that represent what content is consumable for the subscriber. Excluding entitlements will cause no change to the entitlements that are stored for this subscriber. Providing an empty array will clear the subscriber's entitlements
}
type LocalizedString = string | object
type Entitlement = {
  entitlementId: string
  startTime?: string
  endTime?: string
}
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                                           // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean                            // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                                              // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
type Intent = {
  action: string
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type IntentProperties = {
  action: any
  data: any
  context: any
}
type MovieEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVEpisodeEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
type TVSeriesEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVSeasonEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  assetId?: string
  appContentData?: string
}
type AdditionalEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type UntypedEntity = {
  entityId: string
  assetId?: string
  appContentData?: string
}
type ChannelEntity = {
  entityType: "channel"
  channelType: 'streaming' | 'overTheAir'
  entityId: string                         // ID of the channel, in the target App's scope.
  appContentData?: string
}
type ProgramEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
}
type Identifier = string


type Event = 'navigateTo' | 'policyChanged'
enum AudioProfile {
    STEREO = 'stereo',
    DOLBY_DIGITAL_5_1 = 'dolbyDigital5.1',
    DOLBY_DIGITAL_7_1 = 'dolbyDigital7.1',
    DOLBY_DIGITAL_5_1_PLUS = 'dolbyDigital5.1+',
    DOLBY_DIGITAL_7_1_PLUS = 'dolbyDigital7.1+',
    DOLBY_ATMOS = 'dolbyAtmos'
}
enum ProgramType {
    MOVIE = 'movie',
    EPISODE = 'episode',
    SEASON = 'season',
    SERIES = 'series',
    OTHER = 'other',
    PREVIEW = 'preview',
    EXTRA = 'extra',
    CONCERT = 'concert',
    SPORTING_EVENT = 'sportingEvent',
    ADVERTISEMENT = 'advertisement',
    MUSIC_VIDEO = 'musicVideo',
    MINISODE = 'minisode'
}
enum OfferingType {
    FREE = 'free',
    SUBSCRIBE = 'subscribe',
    BUY = 'buy',
    RENT = 'rent'
}

/**
 * get the discovery policy
 */
function policy(): Promise<DiscoveryPolicy>
/**
 * get the discovery policy
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function policy(subscriber: (policy: DiscoveryPolicy) => void): Promise<number>
/**
 * Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow.
 *
 * @param {string} correlationId undefined
 * @param {EntityInfoResult} result The entityInfo data.
 */
/**
 * Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow.
 *
 * @param {string} correlationId undefined
 * @param {EntityInfoResult} result The entityInfo data.
 */
function entityInfo(data: EntityInfoResult): Promise<boolean>

/**
 * Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow.
 *
 * @param {string} correlationId undefined
 * @param {EntityInfoResult} result The entityInfo data.
 */
function entityInfo(callback: (parameters: EntityInfoParameters) => Promise<EntityInfoResult>): Promise<boolean>

/**
 * Provide a list of purchased content for the authenticated account, such as rentals and electronic sell through purchases.
 *
 * @param {string} correlationId undefined
 * @param {PurchasedContentResult} result The data for the purachasedContent
 */
/**
 * Provide a list of purchased content for the authenticated account, such as rentals and electronic sell through purchases.
 *
 * @param {string} correlationId undefined
 * @param {PurchasedContentResult} result The data for the purachasedContent
 */
function purchasedContent(data: PurchasedContentResult): Promise<boolean>

/**
 * Provide a list of purchased content for the authenticated account, such as rentals and electronic sell through purchases.
 *
 * @param {string} correlationId undefined
 * @param {PurchasedContentResult} result The data for the purachasedContent
 */
function purchasedContent(callback: (parameters: PurchasedContentParameters) => Promise<PurchasedContentResult>): Promise<boolean>

/**
 * Notify the platform that content was partially or completely watched
 *
 * @param {string} entityId The entity Id of the watched content.
 * @param {number} progress How much of the content has been watched (percentage as 0-1 for VOD, number of seconds for live)
 * @param {boolean} completed Whether or not this viewing is considered "complete," per the app's definition thereof
 * @param {string} watchedOn Date/Time the content was watched, ISO 8601 Date/Time
 */
function watched(entityId: string, progress?: number, completed?: boolean, watchedOn?: string): Promise<boolean>
/**
 * Suggest a call-to-action for this app on the platform home screen
 *
 * @param {LocalizedString} title The title of this call to action
 * @param {ContentIdentifiers} identifiers A set of content identifiers for this call to action
 * @param {string} expires When this call to action should no longer be presented to users
 * @param {object} images A set of images for this call to action
 */
function watchNext(title?: LocalizedString, identifiers?: ContentIdentifiers, expires?: string, images?: object): Promise<boolean>
/**
 * Inform the platform of the users latest entitlements w/in this app.
*
* @deprecated since version 0.10.0.
 *
 * @param {Entitlement[]} entitlements Array of entitlement objects
 */
function entitlements(entitlements: Entitlement[]): Promise<boolean>
/**
 * Inform the platform of what content the user can access either by discovering it or consuming it. Availabilities determine which content is discoverable to a user, while entitlements determine if the user can currently consume that content. Content can be available but not entitled, this means that user can see the content but when they try to open it they must gain an entitlement either through purchase or subscription upgrade. In case the access changed off-device, this API should be called any time the app comes to the foreground to refresh the access. This API should also be called any time the availabilities or entitlements change within the app for any reason. Typical reasons may include the user signing into an account or upgrading a subscription. Less common cases can cause availabilities to change, such as moving to a new service location. When availabilities or entitlements are removed from the subscriber (such as when the user signs out), then an empty array should be given. To clear both, use the Discovery.clearContentAccess convenience API.
 *
 * @param {ContentAccessIdentifiers} ids A list of identifiers that represent content that is discoverable or consumable for the subscriber
 */
function contentAccess(ids: ContentAccessIdentifiers): Promise<void>
/**
 * Clear both availabilities and entitlements from the subscriber. This is equivalent of calling `Discovery.contentAccess({ availabilities: [], entitlements: []})`. This is typically called when the user signs out of an account.
 */
function clearContentAccess(): Promise<void>
/**
 * Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action
 *
 * @param {string} appId The durable app Id of the app to launch
 * @param {NavigationIntent} intent An optional `NavigationIntent` with details about what part of the app to show first, and context around how/why it was launched
 */
function launch(appId: string, intent?: NavigationIntent): Promise<boolean>
/**
 * Inform the platform that your user is signed in, for increased visiblity in search & discovery. Sign-in state is used separately from what content can be access through entitlements and availabilities. Sign-in state may be used when deciding whether to choose this app to handle a user intent. For instance, if the user tries to launch something generic like playing music from an artist, only a signed-in app will be chosen. If the user wants to tune to a channel, only a signed-in app will be chosen to handle that intent. While signIn can optionally include entitlements as those typically change at signIn time, it is recommended to make a separate call to Discovery.contentAccess for entitlements. signIn is not only for when a user explicitly enters login credentials. If an app does not require any credentials from the user to consume content, such as in a free app, then the app should call signIn immediately on launch.
 *
 * @param {Entitlement[]} entitlements Optional array of Entitlements, in case of a different user account, or a long time since last sign-in.
 */
function signIn(entitlements?: Entitlement[]): Promise<boolean>
/**
 * Inform the platform that your user has signed out. See `Discovery.signIn` for more details on how the sign-in state is used.signOut will NOT clear entitlements, the app should make a separate call to Discovery.clearContentAccess. Apps should also call signOut when a login token has expired and the user is now in a signed-out state.
 */
function signOut(): Promise<boolean>


  /**
  * Listen to all Discovery events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Discovery event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'navigateTo', listener: (data: NavigationIntent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'navigateTo', listener: (data: NavigationIntent) => void): Promise<number>


  /**
   * Clear all Discovery listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'policyChanged', listener: (data: DiscoveryPolicy) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'policyChanged', listener: (data: DiscoveryPolicy) => void): Promise<number>


  /**
   * Clear all Discovery listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'pullEntityInfo', listener: (data: EntityInfoFederatedRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'pullEntityInfo', listener: (data: EntityInfoFederatedRequest) => void): Promise<number>


  /**
   * Clear all Discovery listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'pullPurchasedContent', listener: (data: PurchasedContentFederatedRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Discovery event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'pullPurchasedContent', listener: (data: PurchasedContentFederatedRequest) => void): Promise<number>


  /**
   * Clear all Discovery listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}



}
export module Keyboard {



enum EmailUsage {
    SIGN_IN = 'signIn',
    SIGN_UP = 'signUp'
}

/**
 * Prompt the user for their email address with a simplified list of choices.
 *
 * @param {EmailUsage} type Why the email is being requested, e.g. sign on or sign up
 * @param {string} message The message to display while prompting
 */
function email(type: EmailUsage, message?: string): Promise<string>
/**
 * Show the password entry keyboard, with typing obfuscated from visibility
 *
 * @param {string} message The message to display while prompting
 */
function password(message?: string): Promise<string>
/**
 * Show the standard platform keyboard, and return the submitted value
 *
 * @param {string} message The message to display while prompting
 */
function standard(message: string): Promise<string>





}
export module Lifecycle {
type ListenResponse = {
  event: string
  listening: boolean
}
type LifecycleEvent = {
  state: LifecycleState        // The application lifecycle state
  previous: LifecycleState     // The application lifecycle state
  source?: 'voice' | 'remote'  // The source of the lifecycle change.
}


type Event = 'inactive' | 'foreground' | 'background' | 'suspended' | 'unloading'
enum CloseReason {
    REMOTE_BUTTON = 'remoteButton',
    USER_EXIT = 'userExit',
    DONE = 'done',
    ERROR = 'error'
}
enum LifecycleState {
    INITIALIZING = 'initializing',
    INACTIVE = 'inactive',
    FOREGROUND = 'foreground',
    BACKGROUND = 'background',
    UNLOADING = 'unloading',
    SUSPENDED = 'suspended'
}

/**
 * Notify the platform that the app is ready
 */
function ready(): Promise<void>
/**
 * Request that the platform move your app out of focus
 *
 * @param {CloseReason} reason The reason the app is requesting to be closed
 */
function close(reason: CloseReason): Promise<void>
/**
 * Notify the platform that the app is done unloading
 */
function finished(): Promise<void>
/**
 * Get the current state of the app. This function is **synchronous**.
 */
function state(): LifecycleState


  /**
  * Listen to all Lifecycle events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Lifecycle event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'inactive', listener: (data: LifecycleEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'inactive', listener: (data: LifecycleEvent) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'foreground', listener: (data: LifecycleEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'foreground', listener: (data: LifecycleEvent) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'background', listener: (data: LifecycleEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'background', listener: (data: LifecycleEvent) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'suspended', listener: (data: LifecycleEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'suspended', listener: (data: LifecycleEvent) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'unloading', listener: (data: LifecycleEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'unloading', listener: (data: LifecycleEvent) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Localization {
type ListenResponse = {
  event: string
  listening: boolean
}
type LatLon = [number, number]
type Locality = string
type CountryCode = string
type Language = string
type Locale = string


type Event = 'localityChanged' | 'postalCodeChanged' | 'countryCodeChanged' | 'languageChanged' | 'localeChanged'

/**
 * Get the locality/city the device is located in
 */
function locality(): Promise<string>
/**
 * Get the locality/city the device is located in
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function locality(subscriber: (locality: string) => void): Promise<number>
/**
 * Get the locality/city the device is located in
 *
 * @param {string} value The new locality value.
 */
function locality(value: string): Promise<void>
/**
 * Get the postal code the device is located in
 */
function postalCode(): Promise<string>
/**
 * Get the postal code the device is located in
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function postalCode(subscriber: (postalCode: string) => void): Promise<number>
/**
 * Get the postal code the device is located in
 *
 * @param {string} value The new postalCode value.
 */
function postalCode(value: string): Promise<void>
/**
 * Get the ISO 3166 code for the counrty device is located in
 */
function countryCode(): Promise<string>
/**
 * Get the ISO 3166 code for the counrty device is located in
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function countryCode(subscriber: (code: string) => void): Promise<number>
/**
 * Get the ISO 3166 code for the counrty device is located in
 *
 * @param {string} value The new countryCode value.
 */
function countryCode(value: string): Promise<void>
/**
 * Get the ISO 639 1/2 code for the preferred language
 */
function language(): Promise<string>
/**
 * Get the ISO 639 1/2 code for the preferred language
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function language(subscriber: (lang: string) => void): Promise<number>
/**
 * Get the ISO 639 1/2 code for the preferred language
 *
 * @param {string} value The new language value.
 */
function language(value: string): Promise<void>
/**
 * Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale
 */
function locale(): Promise<string>
/**
 * Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function locale(subscriber: (locale: string) => void): Promise<number>
/**
 * Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale
 *
 * @param {string} value The new locale value.
 */
function locale(value: string): Promise<void>
/**
 * Get the approximate latitude and longitude coordinates of the device location
 */
function latlon(): Promise<[number, number]>
/**
 * Get any platform-specific localization information, in an Map<string, string>
 */
function additionalInfo(): Promise<object>


  /**
  * Listen to all Localization events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Localization event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'localityChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'localityChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Localization listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'postalCodeChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'postalCodeChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Localization listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'countryCodeChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'countryCodeChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Localization listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'languageChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'languageChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Localization listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'localeChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Localization event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'localeChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all Localization listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Metrics {
type MediaPosition = void | number | number
type FlatMap = {
  [property: string]: string | number | boolean
}



enum ErrorType {
    NETWORK = 'network',
    MEDIA = 'media',
    RESTRICTION = 'restriction',
    ENTITLEMENT = 'entitlement',
    OTHER = 'other'
}

/**
 * Inform the platform that your user has started content.
 *
 * @param {string} entityId Optional entity ID of the content.
 */
function startContent(entityId?: string): Promise<boolean>
/**
 * Inform the platform that your user has stopped content.
 *
 * @param {string} entityId Optional entity ID of the content.
 */
function stopContent(entityId?: string): Promise<boolean>
/**
 * Inform the platform that your user has navigated to a page or view.
 *
 * @param {string} pageId Page ID of the content.
 */
function page(pageId: string): Promise<boolean>
/**
 * Inform the platform of something not covered by other Metrics APIs.
 *
 * @param {'user' | 'app'} category The category of action being logged. Must be 'user' for user-initated actions or 'app' for all other actions
 * @param {string} type A short, indexible identifier for the action, e.g. 'SignIn Prompt Displayed'
 * @param {object} parameters undefined
 */
function action(category: 'user' | 'app', type: string, parameters?: object): Promise<boolean>
/**
 * Inform the platform of an error that has occured in your app.
 *
 * @param {ErrorType} type The type of error
 * @param {string} code an app-specific error code
 * @param {string} description A short description of the error
 * @param {boolean} visible Whether or not this error was visible to the user.
 * @param {object} parameters Optional additional parameters to be logged with the error
 */
function error(type: ErrorType, code: string, description: string, visible: boolean, parameters?: object): Promise<boolean>
/**
 * Called when setting the URL of a media asset to play, in order to infer load time.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaLoadStart(entityId: string): Promise<boolean>
/**
 * Called when media playback should start due to autoplay, user-initiated play, or unpausing.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaPlay(entityId: string): Promise<boolean>
/**
 * Called when media playback actually starts due to autoplay, user-initiated play, unpausing, or recovering from a buffering interuption.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaPlaying(entityId: string): Promise<boolean>
/**
 * Called when media playback will pause due to an intentional pause operation.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaPause(entityId: string): Promise<boolean>
/**
 * Called when media playback will halt due to a network, buffer, or other unintentional constraint.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaWaiting(entityId: string): Promise<boolean>
/**
 * Called every 60 seconds as media playback progresses.
 *
 * @param {string} entityId The entityId of the media.
 * @param {MediaPosition} progress Progress of playback, as a decimal percentage (0-0.999) for content with a known duration, or an integer number of seconds (0-86400) for content with an unknown duration.
 */
function mediaProgress(entityId: string, progress: MediaPosition): Promise<boolean>
/**
 * Called when a seek is initiated during media playback.
 *
 * @param {string} entityId The entityId of the media.
 * @param {MediaPosition} target Target destination of the seek, as a decimal percentage (0-0.999) for content with a known duration, or an integer number of seconds (0-86400) for content with an unknown duration.
 */
function mediaSeeking(entityId: string, target: MediaPosition): Promise<boolean>
/**
 * Called when a seek is completed during media playback.
 *
 * @param {string} entityId The entityId of the media.
 * @param {MediaPosition} position Resulting position of the seek operation, as a decimal percentage (0-0.999) for content with a known duration, or an integer number of seconds (0-86400) for content with an unknown duration.
 */
function mediaSeeked(entityId: string, position: MediaPosition): Promise<boolean>
/**
 * Called when the playback rate of media is changed.
 *
 * @param {string} entityId The entityId of the media.
 * @param {number} rate The new playback rate.
 */
function mediaRateChange(entityId: string, rate: number): Promise<boolean>
/**
 * Called when the playback rendition (e.g. bitrate, dimensions, profile, etc) is changed.
 *
 * @param {string} entityId The entityId of the media.
 * @param {number} bitrate The new bitrate in kbps.
 * @param {number} width The new resolution width.
 * @param {number} height The new resolution height.
 * @param {string} profile A description of the new profile, e.g. 'HDR' etc.
 */
function mediaRenditionChange(entityId: string, bitrate: number, width: number, height: number, profile?: string): Promise<boolean>
/**
 * Called when playback has stopped because the end of the media was reached.
 *
 * @param {string} entityId The entityId of the media.
 */
function mediaEnded(entityId: string): Promise<boolean>





}
export module Parameters {
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                                           // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean                            // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                                              // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
type Intent = {
  action: string
  context: {
    source: 'voice' | 'channel-lineup' | 'editorial' | 'device'
  }
}
type IntentProperties = {
  action: any
  data: any
  context: any
}
type MovieEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVEpisodeEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
type TVSeriesEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVSeasonEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  seriesId: string
  assetId?: string
  appContentData?: string
}
type AdditionalEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
  assetId?: string
  appContentData?: string
}
type UntypedEntity = {
  entityId: string
  assetId?: string
  appContentData?: string
}
type ChannelEntity = {
  entityType: "channel"
  channelType: 'streaming' | 'overTheAir'
  entityId: string                         // ID of the channel, in the target App's scope.
  appContentData?: string
}
type ProgramEntity = {
  entityType: "program"
  programType: ProgramType  // In the case of a program `entityType`, specifies the program type.
  entityId: string
}
type Identifier = string
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}
type AppInitialization = {
  us_privacy?: string                  // The IAB US Privacy string.
  lmt?: number                         // The IAB limit ad tracking opt out value.
  discovery?: {
    navigateTo?: NavigationIntent      // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
  }
  secondScreen?: {
    launchRequest?: SecondScreenEvent  // An a message notification from a second screen device
  }
}



enum ProgramType {
    MOVIE = 'movie',
    EPISODE = 'episode',
    SEASON = 'season',
    SERIES = 'series',
    OTHER = 'other',
    PREVIEW = 'preview',
    EXTRA = 'extra',
    CONCERT = 'concert',
    SPORTING_EVENT = 'sportingEvent',
    ADVERTISEMENT = 'advertisement',
    MUSIC_VIDEO = 'musicVideo',
    MINISODE = 'minisode'
}

/**
 * Returns any initialization parameters for the app, e.g. initialial `NavigationIntent`.
 */
function initialization(): Promise<AppInitialization>





}
export module Profile {
type FlatMap = {
  [property: string]: string | number | boolean
}




/**
 * Verifies that the current profile should have access to mature/adult content.
 */
function approveContentRating(): Promise<boolean>
/**
 * Verifies that the current profile should have access to making purchases.
 */
function approvePurchase(): Promise<boolean>
/**
 * Get a map of profile flags for the current session.
 */
function flags(): Promise<object>





}
export module SecondScreen {
type ListenResponse = {
  event: string
  listening: boolean
}
type BooleanMap = {
  [property: string]: boolean
}
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}


type Event = 'launchRequest' | 'closeRequest' | 'friendlyNameChanged'

/**
 * Get the supported second screen discovery protocols
 */
function protocols(): Promise<object>
/**
 * Get the broadcasted id for the device
 *
 * @param {string} type The type of second screen protocol, e.g. "dial"
 */
function device(type?: string): Promise<string>
/**
 * Get the broadcasted friendly name for the device
 */
function friendlyName(): Promise<string>
/**
 * Get the broadcasted friendly name for the device
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function friendlyName(subscriber: (friendlyName: string) => void): Promise<number>


  /**
  * Listen to all SecondScreen events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any SecondScreen event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'launchRequest', listener: (data: SecondScreenEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'launchRequest', listener: (data: SecondScreenEvent) => void): Promise<number>


  /**
   * Clear all SecondScreen listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'closeRequest', listener: (data: SecondScreenEvent) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'closeRequest', listener: (data: SecondScreenEvent) => void): Promise<number>


  /**
   * Clear all SecondScreen listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'friendlyNameChanged', listener: (data: string) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific SecondScreen event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'friendlyNameChanged', listener: (data: string) => void): Promise<number>


  /**
   * Clear all SecondScreen listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module SecureStorage {
type StorageOptions = {
  ttl: number            // Seconds from set time before the data expires and is removed
}



enum StorageScope {
    DEVICE = 'device',
    ACCOUNT = 'account'
}

/**
 * Get stored value by key
 *
 * @param {StorageScope} scope The scope of the key/value
 * @param {string} key Key to get
 */
function get(scope: StorageScope, key: string): Promise<string | null>
/**
 * Set or update a secure data value
 *
 * @param {StorageScope} scope The scope of the data key
 * @param {string} key Key to set
 * @param {string} value Value to set
 * @param {StorageOptions} options Optional parameters to set
 */
function set(scope: StorageScope, key: string, value: string, options?: StorageOptions): Promise<void>
/**
 * Remove a secure data value
 *
 * @param {StorageScope} scope The scope of the data key
 * @param {string} key Key to remove
 */
function remove(scope: StorageScope, key: string): Promise<void>





}
export module VoiceGuidance {
type ListenResponse = {
  event: string
  listening: boolean
}
type VoiceSpeed = number


type Event = 'enabledChanged' | 'speedChanged'

/**
 * Whether or not voice-guidance is enabled.
 */
function enabled(): Promise<boolean>
/**
 * Whether or not voice-guidance is enabled.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function enabled(subscriber: (enabled: boolean) => void): Promise<number>
/**
 * Whether or not voice-guidance is enabled.
 *
 * @param {boolean} value The new enabled value.
 */
function enabled(value: boolean): Promise<void>
/**
 * The speed at which voice guidance speech will be read back to the user.
 */
function speed(): Promise<VoiceSpeed>
/**
 * The speed at which voice guidance speech will be read back to the user.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function speed(subscriber: (speed: VoiceSpeed) => void): Promise<number>
/**
 * The speed at which voice guidance speech will be read back to the user.
 *
 * @param {VoiceSpeed} value The new speed value.
 */
function speed(value: VoiceSpeed): Promise<void>


  /**
  * Listen to all VoiceGuidance events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any VoiceGuidance event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific VoiceGuidance event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'enabledChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific VoiceGuidance event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'enabledChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all VoiceGuidance listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific VoiceGuidance event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'speedChanged', listener: (data: VoiceSpeed) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific VoiceGuidance event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'speedChanged', listener: (data: VoiceSpeed) => void): Promise<number>


  /**
   * Clear all VoiceGuidance listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}