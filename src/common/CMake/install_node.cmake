################################################### Installation & Services ###################################################
# Needs a check here to see if linux :D

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME_STRING=\"${PROJECT_NAME}\")

configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service)
configure_file(${SKYFRAME_ROOT}/src/config/service_template.service ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}@.service
        DESTINATION /etc/systemd/system)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
        DESTINATION /etc/systemd/system)

install(FILES ${PROJECT_NAME}.toml
        RENAME default.toml
        DESTINATION /usr/local/etc/${PROJECT_NAME}/)
