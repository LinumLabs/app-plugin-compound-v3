#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
// EDIT THIS: Put in the number of selectors your plugin is going to support.
#define NUM_SELECTORS 2

// Name of the plugin.
// EDIT THIS: Replace with your plugin name.
#define PLUGIN_NAME "COMPOUND"

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
// EDIT THIS: Change the naming (`selector_t`), and add your selector names.
typedef enum {
   SUPPLY = 0,
   APPROVE = 1
} selector_t;

// Enumeration used to parse the smart contract data.
// EDIT THIS: Adapt the parameter names here.
typedef enum {
    ASSET,
    SPENDER,
    AMOUNT,
    UNEXPECTED_PARAMETER,
} parameter;

// EDIT THIS: Rename `BOILERPLATE` to be the same as the one initialized in `main.c`.
extern const uint32_t COMPOUND_SELECTORS[NUM_SELECTORS];

typedef struct compoundAssetDefinition_t {
    uint8_t address[ADDRESS_LENGTH];
    char assetName[MAX_TICKER_LEN];
    uint8_t decimals;
} compoundAssetDefinition_t;

#define NUM_COMPOUND_ASSETS 2
extern compoundAssetDefinition_t const COMPOUND_ASSETS[NUM_COMPOUND_ASSETS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
// EDIT THIS: This struct is used by your plugin to save the parameters you parse. You
// will need to adapt this struct to your plugin.
typedef struct context_t {
    // For display.
    uint8_t asset[ADDRESS_LENGTH];
    uint8_t spender[ADDRESS_LENGTH];
    uint8_t amount[INT256_LENGTH];
    char ticker[MAX_TICKER_LEN];
    uint8_t decimals;
    uint8_t token_found;

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);