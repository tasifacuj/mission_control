#pragma once



namespace msp_telemetry{
    enum class FirmwareVariant : int {
        NONE = 0, /**< not specified */
        MWII = 1, /**< MultiWii */
        BAFL = 2, /**< BetaFlight */
        BTFL = 3, /**< ButterFlight */
        CLFL = 4, /**< CleanFlight */
        INAV = 5, /**< INAV */
        RCFL = 6  /**< RaceFlight */
    };
}