$version: "2"
namespace com.firebolt.closedcaptions

use com.firebolt#property

service ClosedcaptionsService {
    version: "1.0"
    operations: [enabled, fontFamily, fontSize, fontColor, fontEdge, fontEdgeColor, fontOpacity, backgroundColor, backgroundOpacity, textAlign, textAlignVertical, windowColor, windowOpacity, preferredLanguages]
}

@property
operation enabled {
    input: EnabledInput
    output: EnabledOutput
}

structure EnabledInput {
}

structure EnabledOutput {
    @required
    value: Boolean
}

@property
operation fontFamily {
    input: FontFamilyInput
    output: FontFamilyOutput
}

structure FontFamilyInput {
}

structure FontFamilyOutput {
    @required
    value: FontFamily
}

@property
operation fontSize {
    input: FontSizeInput
    output: FontSizeOutput
}

structure FontSizeInput {
}

structure FontSizeOutput {
    @required
    value: FontSize
}

@property
operation fontColor {
    input: FontColorInput
    output: FontColorOutput
}

structure FontColorInput {
}

structure FontColorOutput {
    @required
    value: Color
}

@property
operation fontEdge {
    input: FontEdgeInput
    output: FontEdgeOutput
}

structure FontEdgeInput {
}

structure FontEdgeOutput {
    @required
    value: FontEdge
}

@property
operation fontEdgeColor {
    input: FontEdgeColorInput
    output: FontEdgeColorOutput
}

structure FontEdgeColorInput {
}

structure FontEdgeColorOutput {
    @required
    value: Color
}

@property
operation fontOpacity {
    input: FontOpacityInput
    output: FontOpacityOutput
}

structure FontOpacityInput {
}

structure FontOpacityOutput {
    @required
    value: Opacity
}

@property
operation backgroundColor {
    input: BackgroundColorInput
    output: BackgroundColorOutput
}

structure BackgroundColorInput {
}

structure BackgroundColorOutput {
    @required
    value: Color
}

@property
operation backgroundOpacity {
    input: BackgroundOpacityInput
    output: BackgroundOpacityOutput
}

structure BackgroundOpacityInput {
}

structure BackgroundOpacityOutput {
    @required
    value: Opacity
}

@property
operation textAlign {
    input: TextAlignInput
    output: TextAlignOutput
}

structure TextAlignInput {
}

structure TextAlignOutput {
    @required
    value: HorizontalAlignment
}

@property
operation textAlignVertical {
    input: TextAlignVerticalInput
    output: TextAlignVerticalOutput
}

structure TextAlignVerticalInput {
}

structure TextAlignVerticalOutput {
    @required
    value: VerticalAlignment
}

@property
operation windowColor {
    input: WindowColorInput
    output: WindowColorOutput
}

structure WindowColorInput {
}

structure WindowColorOutput {
    @required
    value: Color
}

@property
operation windowOpacity {
    input: WindowOpacityInput
    output: WindowOpacityOutput
}

structure WindowOpacityInput {
}

structure WindowOpacityOutput {
    @required
    value: Opacity
}

@property
operation preferredLanguages {
    input: PreferredLanguagesInput
    output: PreferredLanguagesOutput
}

structure PreferredLanguagesInput {
}

structure PreferredLanguagesOutput {
    @required
    value: ISO639_2LanguageList
}

structure ClosedCaptionsSettingsProviderRequest {
    parameters: String
}

enum FontEdge {
    D_E_P_R_E_S_S_E_D = "DEPRESSED"
    D_R_O_P__S_H_A_D_O_W__L_E_F_T = "DROP_SHADOW_LEFT"
    D_R_O_P__S_H_A_D_O_W__R_I_G_H_T = "DROP_SHADOW_RIGHT"
    N_O_N_E = "NONE"
    R_A_I_S_E_D = "RAISED"
    U_N_I_F_O_R_M = "UNIFORM"
}

enum FontFamily {
    C_A_S_U_A_L = "CASUAL"
    C_U_R_S_I_V_E = "CURSIVE"
    M_O_N_O_S_P_A_C_E_D__S_A_N_S_E_R_I_F = "MONOSPACED_SANSERIF"
    M_O_N_O_S_P_A_C_E_D__S_E_R_I_F = "MONOSPACED_SERIF"
    P_R_O_P_O_R_T_I_O_N_A_L__S_A_N_S_E_R_I_F = "PROPORTIONAL_SANSERIF"
    P_R_O_P_O_R_T_I_O_N_A_L__S_E_R_I_F = "PROPORTIONAL_SERIF"
    S_M_A_L_L_C_A_P_S = "SMALLCAPS"
}

list ISO639_2LanguageList {
    member: ISO639_2Language
}

structure Color {
    @required
    value: String
}

structure FontSize {
    @required
    value: Float
}

structure HorizontalAlignment {
    @required
    value: String
}

structure ISO639_2Language {
    @required
    value: String
}

structure Opacity {
    @required
    value: Float
}

structure VerticalAlignment {
    @required
    value: String
}
