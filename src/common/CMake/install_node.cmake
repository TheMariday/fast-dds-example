
################################################### Installation & Services ###################################################

# Find the configuration root, either in program data if windows or user local etc on linux.

if (WIN32)
   file(TO_CMAKE_PATH "$ENV{ProgramData}" PROGRAM_DATA_PATH)
   file(TO_CMAKE_PATH "$ENV{ProgramData}/skyframe" CONFIG_ROOT)
elseif(UNIX AND NOT APPLE)
    file(TO_CMAKE_PATH "/etc/skyframe" CONFIG_ROOT)
else()
    message(FATAL_ERROR "Cannot determine if system is Windows or linux, therefore failed to set the config root")
endif()

message("CONFIG_ROOT set to ${CONFIG_ROOT}")

# Install the default toml file
install(FILES ${PROJECT_NAME}.toml
        RENAME default.toml
        DESTINATION ${CONFIG_ROOT}/${PROJECT_NAME}/)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR})

# Important definition required to pass the PROJECT_NAME to the participantQos
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME_STRING=\"${PROJECT_NAME}\")
target_compile_definitions(${PROJECT_NAME} PRIVATE CONFIG_ROOT=\"${CONFIG_ROOT}\")


# If we're on linux, prepare systemd services for installation
if(UNIX AND NOT APPLE)
    configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service)
    configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service
            DESTINATION /etc/systemd/system)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
            DESTINATION /etc/systemd/system)

endif()