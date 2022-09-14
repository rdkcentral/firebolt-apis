export module Accessibility {
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
type ClosedCaptionsSettings = {
  enabled: boolean               // Whether or not closed-captions should be enabled by default
  styles: ClosedCaptionsStyles   // The default styles to use when displaying closed-captions
}
type VoiceGuidanceSettings = {
  enabled: boolean              // Whether or not voice guidance should be enabled by default
  speed: number                 // The speed at which voice guidance speech will be read back to the user
}

type ListenResponse = {
  event: string
  listening: boolean
}

type Event = 'closedCaptionsSettingsChanged' | 'voiceGuidanceSettingsChanged'

/**
 * Get the user's preferred closed-captions settings
*
* @deprecated since version 0.6.0.
 */
function closedCaptions(): Promise<ClosedCaptionsSettings>
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
type AdPolicy = {
  skipRestriction?: SkipRestriction  // The advertisement skip restriction.
  limitAdTracking?: boolean
}
type AdConfigurationOptions = {
  coppa?: boolean                // Whether or not the app requires US COPPA compliance.
  environment?: 'prod' | 'test'  // Whether the app is running in a production or test mode.
  authenticationEntity?: string  // The authentication provider, when it is separate entity than the app provider, e.g. an MVPD.
}

type ListenResponse = {
  event: string
  listening: boolean
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
 * @param {TokenType} type What type of token to get
 * @param {object} options Additional options for acquiring the token.
 */
function token(type: TokenType, options?: object): Promise<object>





}
export module Device {
type Resolution = [number, number]
type AudioProfiles = {
  stereo: boolean
  "dolbyDigital5.1": boolean
  "dolbyDigital7.1": boolean
  "dolbyDigital5.1+": boolean
  "dolbyDigital7.1+": boolean
  dolbyAtmos: boolean
}

type SemanticVersion = {
  major: number
  minor: number
  patch: number
  readable: string
}
type BooleanMap = {
  [property: string]: boolean
}
type ListenResponse = {
  event: string
  listening: boolean
}
type AudioProfile = 'stereo' | 'dolbyDigital5.1' | 'dolbyDigital7.1' | 'dolbyDigital5.1+' | 'dolbyDigital7.1+' | 'dolbyAtmos'

type Event = 'deviceNameChanged' | 'hdcpChanged' | 'hdrChanged' | 'audioChanged' | 'screenResolutionChanged' | 'videoResolutionChanged' | 'nameChanged' | 'networkChanged'
enum NetworkType {
    WIFI = 'wifi',
    ETHERNET = 'ethernet',
    HYBRID = 'hybrid'
}
enum NetworkState {
    CONNECTED = 'connected',
    DISCONNECTED = 'disconnected'
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
function hdcp(): Promise<BooleanMap>
/**
 * Get the supported HDCP profiles
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function hdcp(subscriber: (supportedHdcpProfiles: BooleanMap) => void): Promise<number>
/**
 * Get the supported HDR profiles
 */
function hdr(): Promise<BooleanMap>
/**
 * Get the supported HDR profiles
 *
 * @param {Function} subscriber A subscriber callback to pass updated values to
 */
function hdr(subscriber: (supportedHdrProfiles: BooleanMap) => void): Promise<number>
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
  function listen(event: 'hdcpChanged', listener: (data: BooleanMap) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'hdcpChanged', listener: (data: BooleanMap) => void): Promise<number>


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
  function listen(event: 'hdrChanged', listener: (data: BooleanMap) => void): Promise<number>

  /**
   * Listen to one and only one instance of a specific Device event.
   * @param {Event} event The Event to listen to.
   * @param {Function} listener The listener function to handle the event.
   */
  function once(event: 'hdrChanged', listener: (data: BooleanMap) => void): Promise<number>


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
type FederatedResponse = {
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
type EntityInfoFederatedResponse = {
  correlationId: string
  result: EntityInfoResult            // The result for an `entityInfo()` push or pull.
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
type PurchasedContentFederatedResponse = {
  correlationId: string
  result: PurchasedContentResult
}
type PurchasedContentResult = {
  expires: string
  totalCount: number
  entries: EntityInfo[]
}

type LocalizedString = string | object
type Entitlement = {
  entitlementId: string
  startTime?: string
  endTime?: string
}
type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
type ListenResponse = {
  event: string
  listening: boolean
}
type ProgramType = 'movie' | 'episode' | 'season' | 'series' | 'other' | 'preview' | 'extra' | 'concert' | 'sportingEvent' | 'advertisement' | 'musicVideo' | 'minisode'
type OfferingType = 'free' | 'subscribe' | 'buy' | 'rent'
type AudioProfile = 'stereo' | 'dolbyDigital5.1' | 'dolbyDigital7.1' | 'dolbyDigital5.1+' | 'dolbyDigital7.1+' | 'dolbyAtmos'
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                        // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean         // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                           // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
type Intent = {
  action: string
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type IntentProperties = {
  action: any
  data: any
  context: any
}
type MovieEntity = {
  entityType: "program"
  programType: "movie"
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVEpisodeEntity = {
  entityType: "program"
  programType: "episode"
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
type TVSeriesEntity = {
  entityType: "program"
  programType: "series"
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVSeasonEntity = {
  entityType: "program"
  programType: "season"
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
 * Inform the platform of the users latest entitlements w/in this app
 *
 * @param {Entitlement[]} entitlements Array of entitlement objects
 */
function entitlements(entitlements: Entitlement[]): Promise<boolean>
/**
 * Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action
 *
 * @param {string} appId The durable app Id of the app to launch
 * @param {NavigationIntent} intent An optional `NavigationIntent` with details about what part of the app to show first, and context around how/why it was launched
 */
function launch(appId: string, intent?: NavigationIntent): Promise<boolean>
/**
 * Inform the platform that your user is signed in, for increased visiblity in search & discovery.
 *
 * @param {Entitlement[]} entitlements Optional array of Entitlements, in case of a different user account, or a long time since last sign-in.
 */
function signIn(entitlements?: Entitlement[]): Promise<boolean>
/**
 * Inform the platform that your user has signed out and that entitlements may no longer be valid.
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
type LifecycleEvent = {
  state: LifecycleState        // The application lifecycle state
  previous: LifecycleState     // The application lifecycle state
  source?: 'voice' | 'remote'  // The source of the lifecycle change.
}

type CloseReason = 'remoteButton' | 'userExit' | 'error'
type LifecycleState = 'initializing' | 'inactive' | 'foreground' | 'background' | 'unloading' | 'suspended'
type ListenResponse = {
  event: string
  listening: boolean
}

type Event = 'inactive' | 'foreground' | 'background' | 'suspended' | 'unloading'

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
type LatLon = [number, number]

type ListenResponse = {
  event: string
  listening: boolean
}

type Event = 'languageChanged'

/**
 * Get the locality/city the device is located in
 */
function locality(): Promise<string>
/**
 * Get the postal code the device is located in
 */
function postalCode(): Promise<string>
/**
 * Get the ISO 3166 code for the counrty device is located in
 */
function countryCode(): Promise<string>
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
 * Get the *full* BCP 47 code, including script, region, variant, etc., for the preferred langauage/locale
 */
function locale(): Promise<string>
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
 * @param {FlatMap} parameters undefined
 */
function action(category: 'user' | 'app', type: string, parameters?: FlatMap): Promise<boolean>
/**
 * Inform the platform of an error that has occured in your app.
 *
 * @param {ErrorType} type The type of error
 * @param {string} code an app-specific error code
 * @param {string} description A short description of the error
 * @param {boolean} visible Whether or not this error was visible to the user.
 * @param {FlatMap} parameters Optional additional parameters to be logged with the error
 */
function error(type: ErrorType, code: string, description: string, visible: boolean, parameters?: FlatMap): Promise<boolean>
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

type NavigationIntent = HomeIntent | LaunchIntent | EntityIntent | PlaybackIntent | SearchIntent | SectionIntent | TuneIntent
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}
type HomeIntent = {
  action: "home"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type LaunchIntent = {
  action: "launch"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type EntityIntent = {
  action: "entity"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | TVSeriesEntity | TVSeasonEntity | AdditionalEntity | UntypedEntity
}
type PlaybackIntent = {
  action: "playback"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: MovieEntity | TVEpisodeEntity | AdditionalEntity
}
type SearchIntent = {
  action: "search"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    query: string
  }
}
type SectionIntent = {
  action: "section"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data?: {
    sectionName: string
  }
}
type TuneIntent = {
  action: "tune"
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
  data: {
    entity: ChannelEntity
    options?: {
      assetId?: string                        // The ID of a specific 'listing', as scoped by the target App's ID-space, which the App should begin playback from.
      restartCurrentProgram?: boolean         // Denotes that the App should start playback at the most recent program boundary, rather than 'live.'
      time?: string                           // ISO 8601 Date/Time where the App should begin playback from.
    }
  }
}
type Intent = {
  action: string
  context: {
    source: 'voice' | 'editorial' | 'device'
  }
}
type IntentProperties = {
  action: any
  data: any
  context: any
}
type MovieEntity = {
  entityType: "program"
  programType: "movie"
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVEpisodeEntity = {
  entityType: "program"
  programType: "episode"
  entityId: string
  seriesId: string
  seasonId: string
  assetId?: string
  appContentData?: string
}
type TVSeriesEntity = {
  entityType: "program"
  programType: "series"
  entityId: string
  assetId?: string
  appContentData?: string
}
type TVSeasonEntity = {
  entityType: "program"
  programType: "season"
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
type ProgramType = 'movie' | 'episode' | 'season' | 'series' | 'other' | 'preview' | 'extra' | 'concert' | 'sportingEvent' | 'advertisement' | 'musicVideo' | 'minisode'



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
function flags(): Promise<FlatMap>





}
export module SecondScreen {

type BooleanMap = {
  [property: string]: boolean
}
type ListenResponse = {
  event: string
  listening: boolean
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
function protocols(): Promise<BooleanMap>
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

export module Extensions {
    function initialize(id: string, config: object): Promise<void>
    function active():Promise<string[]>
}