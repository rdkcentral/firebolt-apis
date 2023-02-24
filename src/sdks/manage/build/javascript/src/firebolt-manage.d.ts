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
export module Accessory {
type AccessoryList = {
  list?: AccessoryInfo[]
}
type AccessoryPairingTimeout = number
type AccessoryInfo = {
  type?: AccessoryType          // Type of the device Remote,Speaker or Other
  make?: string                 // Name of the manufacturer of the accessory
  model?: string                // Model name of the accessory
  protocol?: AccessoryProtocol  // Mechanism to connect the accessory to the device
}



enum AccessoryType {
    REMOTE = 'Remote',
    SPEAKER = 'Speaker',
    OTHER = 'Other'
}
enum AccessoryTypeListParam {
    REMOTE = 'Remote',
    SPEAKER = 'Speaker',
    ALL = 'All'
}
enum AccessoryProtocol {
    BLUETOOTH_LE = 'BluetoothLE',
    RF4CE = 'RF4CE'
}
enum AccessoryProtocolListParam {
    BLUETOOTH_LE = 'BluetoothLE',
    RF4CE = 'RF4CE',
    ALL = 'All'
}

/**
 * Pair an accessory with the device.
 *
 * @param {AccessoryType} type undefined
 * @param {AccessoryProtocol} protocol undefined
 * @param {AccessoryPairingTimeout} timeout undefined
 */
function pair(type?: AccessoryType, protocol?: AccessoryProtocol, timeout?: AccessoryPairingTimeout): Promise<AccessoryInfo>
/**
 * Provides a list of Accesories paired to the device.
 *
 * @param {AccessoryTypeListParam} type undefined
 * @param {AccessoryProtocolListParam} protocol Defines the mechanism by which accessory will connect to the device.
 */
function list(type?: AccessoryTypeListParam, protocol?: AccessoryProtocolListParam): Promise<AccessoryList>





}
export module Account {
type ListenResponse = {
  event: string
  listening: boolean
}
type Token = string
type Expiry = number
type Session = {
  token?: string      // Encoded token provided by the Distributor for Device Authentication.
  expiresIn?: number  // Number of secs before the token expires
}
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}




/**
 * Used by a distributor to push Session token to firebolt.
 *
 * @param {string} token undefined
 * @param {number} expiresIn undefined
 */
function session(token?: string, expiresIn?: number): Promise<void>


  /**
  * Listen to all Account events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Account event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Account event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestSession', listener: (data: object) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Account event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestSession', listener: (data: object) => void): Promise<number>


  /**
   * Clear all Account listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}


  interface SessionProvider {
      session(parameters: void, session: FocusableProviderSession):Promise<object>
}

  /**
   * Provide the 'xrn:firebolt:capability:token:session' Capability
   * @param {string} capability The Capability to provide
   * @param {SessionProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:token:session', provider: SessionProvider | object): Promise<void>

}
export module AcknowledgeChallenge {
type ListenResponse = {
  event: string
  listening: boolean
}
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
type ChallengeRequestor = {
  id: string                 // The id of the app that requested the challenge
  name: string               // The name of the app that requested the challenge
}
type Challenge = {
  capability: string             // The capability that is being requested by the user to approve
  requestor: ChallengeRequestor
}
type ChallengeProviderRequest = {
  correlationId: string            // The id that was passed in to the event that triggered a provider method to be called
  parameters: Challenge
}
type GrantResult = {
  granted: boolean    // Whether the user approved or denied the challenge
}
type ProviderRequest = {
  correlationId: string   // The id that was passed in to the event that triggered a provider method to be called
  parameters?: object     // The result of the provider response.
}






  /**
  * Listen to all AcknowledgeChallenge events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any AcknowledgeChallenge event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific AcknowledgeChallenge event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestChallenge', listener: (data: ChallengeProviderRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific AcknowledgeChallenge event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestChallenge', listener: (data: ChallengeProviderRequest) => void): Promise<number>


  /**
   * Clear all AcknowledgeChallenge listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}


  interface ChallengeProvider {
      challenge(parameters: object, session: FocusableProviderSession):Promise<GrantResult>
}

  /**
   * Provide the 'xrn:firebolt:capability:usergrant:acknowledgechallenge' Capability
   * @param {string} capability The Capability to provide
   * @param {ChallengeProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:usergrant:acknowledgechallenge', provider: ChallengeProvider | object): Promise<void>

}
export module Advertising {




/**
 * Resets a user's identifier in the ad platform so that the advertising id that apps get will be a new value
 */
function resetIdentifier(): Promise<void>





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
export module DeveloperTools {
type ListenResponse = {
  event: string
  listening: boolean
}
type DeveloperTool = {
  id: string            // The ID that uniquely identifies this instance of a developer tool
  name: string          // Developer-visible 'friendly name' for the developer tool
}




/**
 * Starts a long-running DNS-SD search for a list of developer tools that match the standard 'Firebolt Developer Tool' service type
 */
function find(add: (item: DeveloperTool) => void, remove: (item: DeveloperTool) => void): { stop: () => {} }
function find(add: (item: DeveloperTool) => void): { stop: () => {} }
/**
 * Configures Firebolt to accept incoming Firebolt JSON RPC messages from the developer tool identified by the given developer tool ID
 *
 * @param {string} id The ID of the DeveloperTool to which to connect
 */
function pair(id: string): Promise<void>
/**
 * Disconnect Firebolt as a web socket client from the web socket that corresponds to the given developer tool ID
 *
 * @param {string} id The ID of the DeveloperTool from which to disconnect
 */
function unpair(id: string): Promise<void>


  /**
  * Listen to all DeveloperTools events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any DeveloperTools event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific DeveloperTools event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'toolAvailable', listener: (data: DeveloperTool) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific DeveloperTools event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'toolAvailable', listener: (data: DeveloperTool) => void): Promise<number>


  /**
   * Clear all DeveloperTools listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific DeveloperTools event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'toolUnavailable', listener: (data: DeveloperTool) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific DeveloperTools event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'toolUnavailable', listener: (data: DeveloperTool) => void): Promise<number>


  /**
   * Clear all DeveloperTools listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Device {
type ListenResponse = {
  event: string
  listening: boolean
}


type Event = 'deviceNameChanged' | 'nameChanged' | 'developerModeChanged'

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
 * Used by a distributor to push provision info to firebolt.
 *
 * @param {string} accountId The id of the account that is device is attached to in the back office.
 * @param {string} deviceId The id of the device in the back office.
 * @param {string} distributorId The id of the distributor in the back office.
 */
function provision(accountId: string, deviceId: string, distributorId?: string): Promise<void>
/**
 * Whether or not developer mode is enabled.
 */
function developerMode(): Promise<boolean>
/**
 * Whether or not developer mode is enabled.
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function developerMode(subscriber: (developerMode: boolean) => void): Promise<number>
/**
 * Whether or not developer mode is enabled.
 *
 * @param {boolean} value The new developerMode value.
 */
function developerMode(value: boolean): Promise<void>


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
  function listen(event: 'developerModeChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'developerModeChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Device listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module Keyboard {
type ListenResponse = {
  event: string
  listening: boolean
}
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
type KeyboardParameters = {
  message: string            // The message to display to the user so the user knows what they are entering
}
type KeyboardProviderRequest = {
  correlationId: string           // An id to correlate the provider response with this request
  parameters: KeyboardParameters
}
type KeyboardResult = {
  text: string           // The text the user entered into the keyboard
  canceled?: boolean     // Whether the user canceled entering text before they were finished typing on the keyboard
}






  /**
  * Listen to all Keyboard events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Keyboard event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestStandard', listener: (data: KeyboardProviderRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestStandard', listener: (data: KeyboardProviderRequest) => void): Promise<number>


  /**
   * Clear all Keyboard listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestPassword', listener: (data: KeyboardProviderRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestPassword', listener: (data: KeyboardProviderRequest) => void): Promise<number>


  /**
   * Clear all Keyboard listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestEmail', listener: (data: KeyboardProviderRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Keyboard event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestEmail', listener: (data: KeyboardProviderRequest) => void): Promise<number>


  /**
   * Clear all Keyboard listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}


  interface KeyboardInputProvider {
      standard(parameters: KeyboardParameters, session: FocusableProviderSession):Promise<KeyboardResult>
      password(parameters: KeyboardParameters, session: FocusableProviderSession):Promise<KeyboardResult>
      email(parameters: KeyboardParameters, session: FocusableProviderSession):Promise<KeyboardResult>
}

  /**
   * Provide the 'xrn:firebolt:capability:input:keyboard' Capability
   * @param {string} capability The Capability to provide
   * @param {KeyboardInputProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:input:keyboard', provider: KeyboardInputProvider | object): Promise<void>

}
export module Lifecycle {
type ListenResponse = {
  event: string
  listening: boolean
}
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

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
type LifecycleReadyParameters = {
  appId: string                    // The application ID
}
type LifecycleLaunchParameters = {
  appId: string                     // The application ID
  intent?: NavigationIntent         // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
}
type LifecycleLaunchResponse = {
  success: boolean                // Whether the launch succeeded
}
type LifecycleCloseParameters = {
  appId: string                    // The application ID
  reason: CloseReason              // The application close reason
}
type LifecycleFinishedParameters = {
  appId: string                       // The application ID
}
type LifecycleReadyRequest = {
  parameters: LifecycleReadyParameters
}
type LifecycleLaunchRequest = {
  parameters: LifecycleLaunchParameters
}
type LifecycleCloseRequest = {
  parameters: LifecycleCloseParameters
}
type LifecycleFinishedRequest = {
  parameters: LifecycleFinishedParameters
}
type AppSession = {
  app: {
    id: string                          // The identifier for the app
    url?: string                        // The url that the app will be launched with
    title?: string                      // The display title of the app
    catalog?: string                    // The catalog id that this app's content metadata comes from
  }
  runtime?: {
    id?: string                         // The identifier for the runtime
    transport?: 'bridge' | 'websocket'  // The type of transport the application container will use to communicate to Firebolt
  }
  launch?: {
    intent?: NavigationIntent           // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
    secondScreen?: SecondScreenEvent    // An a message notification from a second screen device
  }
}
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
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
 * Used by provider to update the state of an application so that the state can be emitted to apps.
 *
 * @param {string} appId undefined
 * @param {LifecycleState} state undefined
 */
function setState(appId: string, state: LifecycleState): Promise<void>
/**
 * Used by a Lifecycle provider to tell Firebolt that an app session has been started or updated. Firebolt can use this information to have context about the app when it makes API requests
 *
 * @param {AppSession} session undefined
 */
function session(session: AppSession): Promise<object>


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
  function listen(event: 'requestLaunch', listener: (data: LifecycleLaunchRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestLaunch', listener: (data: LifecycleLaunchRequest) => void): Promise<number>


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
  function listen(event: 'requestReady', listener: (data: LifecycleReadyRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestReady', listener: (data: LifecycleReadyRequest) => void): Promise<number>


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
  function listen(event: 'requestClose', listener: (data: LifecycleCloseRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestClose', listener: (data: LifecycleCloseRequest) => void): Promise<number>


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
  function listen(event: 'requestFinished', listener: (data: LifecycleFinishedRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Lifecycle event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestFinished', listener: (data: LifecycleFinishedRequest) => void): Promise<number>


  /**
   * Clear all Lifecycle listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}



  interface LaunchProvider {
      launch(parameters: LifecycleLaunchParameters, session: ProviderSession):Promise<LifecycleLaunchResponse>
}

  /**
   * Provide the 'xrn:firebolt:capability:lifecycle:launch' Capability
   * @param {string} capability The Capability to provide
   * @param {LaunchProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:lifecycle:launch', provider: LaunchProvider | object): Promise<void>

  interface StateProvider {
      ready(parameters: LifecycleReadyParameters, session: ProviderSession):Promise<void>
      close(parameters: LifecycleCloseParameters, session: ProviderSession):Promise<void>
      finished(parameters: LifecycleFinishedParameters, session: ProviderSession):Promise<void>
}

  /**
   * Provide the 'xrn:firebolt:capability:lifecycle:state' Capability
   * @param {string} capability The Capability to provide
   * @param {StateProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:lifecycle:state', provider: StateProvider | object): Promise<void>

}
export module Localization {
type ListenResponse = {
  event: string
  listening: boolean
}
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
export module PinChallenge {
type ListenResponse = {
  event: string
  listening: boolean
}
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
type ChallengeRequestor = {
  id: string                 // The id of the app that requested the challenge
  name: string               // The name of the app that requested the challenge
}
type ProviderRequest = {
  correlationId: string   // The id that was passed in to the event that triggered a provider method to be called
  parameters?: object     // The result of the provider response.
}
type PinChallenge = {
  pinSpace: 'purchase' | 'content'  // The pin space that this challenge is for
  capability?: string               // The capability that is gated by a pin challenge
  requestor: ChallengeRequestor
}
type PinChallengeProviderRequest = {
  correlationId: string               // The id that was passed in to the event that triggered a provider method to be called
  parameters: PinChallenge
}
type PinChallengeResult = {
  granted: boolean           // Whether the user succeeded in the pin challenge
  reason: ResultReason       // The reason for the result of challenging the user
}



enum ResultReason {
    NO_PIN_REQUIRED = 'noPinRequired',
    NO_PIN_REQUIRED_WINDOW = 'noPinRequiredWindow',
    EXCEEDED_PIN_FAILURES = 'exceededPinFailures',
    CORRECT_PIN = 'correctPin',
    CANCELLED = 'cancelled'
}



  /**
  * Listen to all PinChallenge events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any PinChallenge event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific PinChallenge event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'requestChallenge', listener: (data: PinChallengeProviderRequest) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific PinChallenge event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'requestChallenge', listener: (data: PinChallengeProviderRequest) => void): Promise<number>


  /**
   * Clear all PinChallenge listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean



interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}


  interface ChallengeProvider {
      challenge(parameters: object, session: FocusableProviderSession):Promise<PinChallengeResult>
}

  /**
   * Provide the 'xrn:firebolt:capability:usergrant:pinchallenge' Capability
   * @param {string} capability The Capability to provide
   * @param {ChallengeProvider} provider The object providing the capability interface
   */
  function provide(capability: 'xrn:firebolt:capability:usergrant:pinchallenge', provider: ChallengeProvider | object): Promise<void>

}
export module Privacy {
type ListenResponse = {
  event: string
  listening: boolean
}
type PrivacySettings = {
  allowACRCollection: boolean
  allowResumePoints: boolean
  allowAppContentAdTargeting: boolean
  allowCameraAnalytics: boolean
  allowPersonalization: boolean
  allowPrimaryBrowseAdTargeting: boolean
  allowPrimaryContentAdTargeting: boolean
  allowProductAnalytics: boolean
  allowRemoteDiagnostics: boolean
  allowUnentitledPersonalization: boolean
  allowUnentitledResumePoints: boolean
  allowWatchHistory: boolean
}


type Event = 'allowResumePointsChanged' | 'allowUnentitledResumePointsChanged' | 'allowWatchHistoryChanged' | 'allowProductAnalyticsChanged' | 'allowPersonalizationChanged' | 'allowUnentitledPersonalizationChanged' | 'allowRemoteDiagnosticsChanged' | 'allowPrimaryContentAdTargetingChanged' | 'allowPrimaryBrowseAdTargetingChanged' | 'allowAppContentAdTargetingChanged' | 'allowACRCollectionChanged' | 'allowCameraAnalyticsChanged'

/**
 * Whether the user allows resume points for content to show in the main experience
 */
function allowResumePoints(): Promise<boolean>
/**
 * Whether the user allows resume points for content to show in the main experience
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowResumePoints(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows resume points for content to show in the main experience
 *
 * @param {boolean} value The new allowResumePoints value.
 */
function allowResumePoints(value: boolean): Promise<void>
/**
 * Whether the user allows resume points for content from unentitled providers to show in the main experience
 */
function allowUnentitledResumePoints(): Promise<boolean>
/**
 * Whether the user allows resume points for content from unentitled providers to show in the main experience
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowUnentitledResumePoints(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows resume points for content from unentitled providers to show in the main experience
 *
 * @param {boolean} value The new allowUnentitledResumePoints value.
 */
function allowUnentitledResumePoints(value: boolean): Promise<void>
/**
 * Whether the user allows their watch history from all sources to show in the main experience
 */
function allowWatchHistory(): Promise<boolean>
/**
 * Whether the user allows their watch history from all sources to show in the main experience
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowWatchHistory(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their watch history from all sources to show in the main experience
 *
 * @param {boolean} value The new allowWatchHistory value.
 */
function allowWatchHistory(value: boolean): Promise<void>
/**
 * Whether the user allows their usage data can be used for analytics about the product
 */
function allowProductAnalytics(): Promise<boolean>
/**
 * Whether the user allows their usage data can be used for analytics about the product
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowProductAnalytics(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their usage data can be used for analytics about the product
 *
 * @param {boolean} value The new allowProductAnalytics value.
 */
function allowProductAnalytics(value: boolean): Promise<void>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations
 */
function allowPersonalization(): Promise<boolean>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowPersonalization(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations
 *
 * @param {boolean} value The new allowPersonalization value.
 */
function allowPersonalization(value: boolean): Promise<void>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations for unentitled content
 */
function allowUnentitledPersonalization(): Promise<boolean>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations for unentitled content
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowUnentitledPersonalization(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their usage data to be used for personalization and recommendations for unentitled content
 *
 * @param {boolean} value The new allowUnentitledPersonalization value.
 */
function allowUnentitledPersonalization(value: boolean): Promise<void>
/**
 * Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device
 */
function allowRemoteDiagnostics(): Promise<boolean>
/**
 * Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowRemoteDiagnostics(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their personal data to be included in diagnostic telemetry. This also allows whether device logs can be remotely accessed from the client device
 *
 * @param {boolean} value The new allowRemoteDiagnostics value.
 */
function allowRemoteDiagnostics(value: boolean): Promise<void>
/**
 * Whether the user allows ads to be targeted to the user while watching content in the primary experience
 */
function allowPrimaryContentAdTargeting(): Promise<boolean>
/**
 * Whether the user allows ads to be targeted to the user while watching content in the primary experience
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowPrimaryContentAdTargeting(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows ads to be targeted to the user while watching content in the primary experience
 *
 * @param {boolean} value The new allowPrimaryContentAdTargeting value.
 */
function allowPrimaryContentAdTargeting(value: boolean): Promise<void>
/**
 * Whether the user allows ads to be targeted to the user while browsing in the primary experience
 */
function allowPrimaryBrowseAdTargeting(): Promise<boolean>
/**
 * Whether the user allows ads to be targeted to the user while browsing in the primary experience
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowPrimaryBrowseAdTargeting(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows ads to be targeted to the user while browsing in the primary experience
 *
 * @param {boolean} value The new allowPrimaryBrowseAdTargeting value.
 */
function allowPrimaryBrowseAdTargeting(value: boolean): Promise<void>
/**
 * Whether the user allows ads to be targeted to the user while watching content in apps
 */
function allowAppContentAdTargeting(): Promise<boolean>
/**
 * Whether the user allows ads to be targeted to the user while watching content in apps
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowAppContentAdTargeting(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows ads to be targeted to the user while watching content in apps
 *
 * @param {boolean} value The new allowAppContentAdTargeting value.
 */
function allowAppContentAdTargeting(value: boolean): Promise<void>
/**
 * Whether the user allows their automatic content recognition data to be collected
 */
function allowACRCollection(): Promise<boolean>
/**
 * Whether the user allows their automatic content recognition data to be collected
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowACRCollection(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows their automatic content recognition data to be collected
 *
 * @param {boolean} value The new allowACRCollection value.
 */
function allowACRCollection(value: boolean): Promise<void>
/**
 * Whether the user allows data from their camera to be used for Product Analytics
 */
function allowCameraAnalytics(): Promise<boolean>
/**
 * Whether the user allows data from their camera to be used for Product Analytics
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function allowCameraAnalytics(subscriber: (allow: boolean) => void): Promise<number>
/**
 * Whether the user allows data from their camera to be used for Product Analytics
 *
 * @param {boolean} value The new allowCameraAnalytics value.
 */
function allowCameraAnalytics(value: boolean): Promise<void>
/**
 * Gets the allowed value for all privacy settings
 */
function settings(): Promise<PrivacySettings>


  /**
  * Listen to all Privacy events.
  * @param {Function} listener The listener function to handle the events.
  */
  function listen(listener: (event: string, data: object) => void): Promise<number>

  /**
  * Listen to one and only one instance of any Privacy event (whichever is first).
  * @param {Function} listener The listener function to handle the events.
  */
  function once(listener: (event: string, data: object) => void): Promise<number>

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowResumePointsChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowResumePointsChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowUnentitledResumePointsChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowUnentitledResumePointsChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowWatchHistoryChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowWatchHistoryChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowProductAnalyticsChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowProductAnalyticsChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowPersonalizationChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowPersonalizationChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowUnentitledPersonalizationChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowUnentitledPersonalizationChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowRemoteDiagnosticsChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowRemoteDiagnosticsChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowPrimaryContentAdTargetingChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowPrimaryContentAdTargetingChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowPrimaryBrowseAdTargetingChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowPrimaryBrowseAdTargetingChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowAppContentAdTargetingChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowAppContentAdTargetingChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowACRCollectionChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowACRCollectionChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean

  /**
   * Listen to a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function listen(event: 'allowCameraAnalyticsChanged', listener: (data: boolean) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Privacy event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'allowCameraAnalyticsChanged', listener: (data: boolean) => void): Promise<number>


  /**
   * Clear all Privacy listeners, or just the listener for a specific Id.
   * @param {id} optional id of the listener to clear.
   */
  function clear(id?: number): boolean




}
export module UserGrants {
type Capability = string
type Permission = {
  role?: Role          // Role provides access level for the app for a given capability.
  capability?: string  // A Capability is a discrete unit of functionality that a Firebolt device might be able to perform.
}
type GrantInfo = {
  app?: {
    id: string
    title?: string
  }
  state: 'granted' | 'denied'                                             // The state the grant is in
  capability: string                                                      // A Capability is a discrete unit of functionality that a Firebolt device might be able to perform.
  role: Role                                                              // Role provides access level for the app for a given capability.
  lifespan: 'once' | 'forever' | 'appActive' | 'powerActive' | 'seconds'
  expires?: string
}
type AppInfo = {
  id: string
  title?: string
}
type GrantModificationOptions = {
  appId?: string
}



enum Role {
    USE = 'use',
    MANAGE = 'manage',
    PROVIDE = 'provide'
}
enum undefined {
    GRANTED = 'granted',
    DENIED = 'denied'
}

/**
 * Get all granted and denied user grants for the given app
 *
 * @param {string} appId undefined
 */
function app(appId: string): Promise<object[]>
/**
 * Get all granted and denied user grants for the device
 */
function device(): Promise<object[]>
/**
 * Get all granted and denied user grants for the given capability
 *
 * @param {string} capability undefined
 */
function capability(capability: string): Promise<object[]>
/**
 * Grants a given capability to a specific app, if appropriate. Calling this results in a persisted active grant that lasts for the duration of the grant policy lifespan. 
 *
 * @param {Role} role undefined
 * @param {string} capability undefined
 * @param {object} options undefined
 */
function grant(role: Role, capability: string, options?: object): Promise<'null'>
/**
 * Denies a given capability, to a specific app if appropriate. Calling this results in a persisted Denied Grant that lasts for the duration of the Grant Policy lifespan. 
 *
 * @param {Role} role undefined
 * @param {string} capability undefined
 * @param {object} options undefined
 */
function deny(role: Role, capability: string, options?: object): Promise<'null'>
/**
 * Clears the grant for a given capability, to a specific app if appropriate. Calling this results in a persisted Denied Grant that lasts for the duration of the Grant Policy lifespan. 
 *
 * @param {Role} role undefined
 * @param {string} capability undefined
 * @param {object} options undefined
 */
function clear(role: Role, capability: string, options?: object): Promise<'null'>
/**
 * Requests Firebolt to carry out a set of user grants for a given application such that the user grant provider is notified or an existing user grant is reused.
 *
 * @param {string} appId undefined
 * @param {Permission[]} permissions undefined
 */
function request(appId: string, permissions: Permission[]): Promise<object[]>





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
export module Wifi {
type AccessPointList = {
  list?: AccessPoint[]
}
type WifiSignalStrength = number
type WifiFrequency = number
type AccessPoint = {
  ssid?: string                        // Name of the wifi.
  securityMode?: WifiSecurityMode      // Security Mode supported for Wifi
  signalStrength?: WifiSignalStrength  // Strength of Wifi signal, value is negative based on RSSI specification.
  frequency?: WifiFrequency            // Wifi Frequency in Ghz, example 2.4Ghz and 5Ghz.
}
type Timeout = number



enum WifiSecurityMode {
    NONE = 'none',
    WEP_64 = 'wep64',
    WEP_128 = 'wep128',
    WPA_PSK_TKIP = 'wpaPskTkip',
    WPA_PSK_AES = 'wpaPskAes',
    WPA_2PSK_TKIP = 'wpa2PskTkip',
    WPA_2PSK_AES = 'wpa2PskAes',
    WPA_ENTERPRISE_TKIP = 'wpaEnterpriseTkip',
    WPA_ENTERPRISE_AES = 'wpaEnterpriseAes',
    WPA_2ENTERPRISE_TKIP = 'wpa2EnterpriseTkip',
    WPA_2ENTERPRISE_AES = 'wpa2EnterpriseAes',
    WPA_2PSK = 'wpa2Psk',
    WPA_2ENTERPRISE = 'wpa2Enterprise',
    WPA_3PSK_AES = 'wpa3PskAes',
    WPA_3SAE = 'wpa3Sae'
}
enum WPSSecurityPin {
    PUSH_BUTTON = 'pushButton',
    PIN = 'pin',
    MANUFACTURER_PIN = 'manufacturerPin'
}

/**
 * Scan available wifi networks in the location.
 *
 * @param {Timeout} timeout undefined
 */
function scan(timeout?: Timeout): Promise<AccessPointList>
/**
 * Connect the device to the specified SSID.
 *
 * @param {string} ssid undefined
 * @param {string} passphrase undefined
 * @param {WifiSecurityMode} security undefined
 */
function connect(ssid?: string, passphrase?: string, security?: WifiSecurityMode): Promise<AccessPoint>
/**
 * Disconnect the device if connected via WIFI.
 */
function disconnect(): Promise<void>
/**
 * Connect to WPS
 *
 * @param {WPSSecurityPin} security undefined
 */
function wps(security?: WPSSecurityPin): Promise<AccessPoint>





}