#include "SystemSetting.h"

SystemSettings current_settings;  // 在这里定义




void save_settings_to_eeprom(SystemSettings *settings) {
    uint16_t address = 0x00;  // EEPROM start address
    uint8_t *settings_ptr = (uint8_t*)settings;  // Cast structure pointer to byte pointer
    
    // Print current settings before saving
    printf("Saving settings: beep_state = %d\n", settings->beep_state);
    
    uint8_t result = eeprom_WriteArrary(&eeprom, address, settings_ptr, sizeof(SystemSettings));
    if (result == EEPROM_NO_ERROR) {
        printf("Settings saved successfully!\n");
    } else {
        printf("Failed to save settings, error code: %d\n", result);
    }
}


void load_settings_from_eeprom(SystemSettings *settings) {
    uint16_t address = 0x00;  // Assume starting address is 0x00
    uint8_t *settings_ptr = (uint8_t*)settings;

    uint8_t result = eeprom_ReadArrary(&eeprom, address, settings_ptr, sizeof(SystemSettings));
    if (result == EEPROM_NO_ERROR) {
        printf("Settings loaded successfully!\n");
        printf("Beeps state: %d\n", settings->beep_state);  // Print beep state after loading
    } else {
        printf("Failed to load settings, error code: %d\n", result);
    }
}



void set_buzzer_status(uint8_t state) {
    if (state) {
        printf("Buzzer turned ON\n");
        // Call hardware-related code to turn on the buzzer
        BEEP_OK();
    } else {
        printf("Buzzer turned OFF\n");
        // Call hardware-related code to turn off the buzzer
        BEEP_OFF();
    }
}

void apply_settings(const SystemSettings *settings) {
    printf("Applying settings:\n");
    printf("Beeps state: %d\n", settings->beep_state);  // Print beep state
    set_buzzer_status(settings->beep_state);  // Set buzzer status
}


void system_init(void) {
    printf("System Initialization Start...\n");
    
    load_settings_from_eeprom(&current_settings);
    printf("Settings Loaded: beep_state = %d\n", current_settings.beep_state);
    
    apply_settings(&current_settings);
    printf("Settings Applied: beep_state = %d\n", current_settings.beep_state);
}

