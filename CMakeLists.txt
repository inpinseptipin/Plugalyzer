cmake_minimum_required(VERSION 3.15)
project(PLUGALYZER VERSION 0.0.1)

# embrace the future, baby!
set(CMAKE_CXX_STANDARD 20)

# include JUCE from submodule

option(AUXPLUG_BUILD_PLUGALYZER_BINARY "Build Plugalyzer Binary " OFF)
option(AUXPLUG_BUILD_IMPULSERESPONSE_TOOL "Build Generate Impulse Response Tool" OFF)

include(FetchContent)

FetchContent_Declare(
	auxport
	GIT_REPOSITORY https://github.com/inpinseptipin/AuxPort
	GIT_TAG master
 )
FetchContent_MakeAvailable(auxport)

FetchContent_Declare(
	JUCE
	GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
	GIT_TAG origin/master
	GIT_SHALLOW ON
	FIND_PACKAGE_ARGS 8.0.0 GLOBAL
)
FetchContent_MakeAvailable(JUCE)

FetchContent_Declare(
	json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG origin/develop
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
	CLI11
	GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
	GIT_TAG origin/main
)	
FetchContent_MakeAvailable(CLI11)











if(AUXPLUG_BUILD_PLUGALYZER_BINARY)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")



juce_add_console_app(Plugalyzer
    COMPANY_NAME CrushedPixel
    )

# include CLI11 from submodule
target_include_directories(Plugalyzer PRIVATE {$CLI11_SOURCE_DIR}/include)
target_include_directories(Plugalyzer PRIVATE {$json_SOURCE_DIR}/include)




target_sources(Plugalyzer
    PRIVATE
    Source/main.cpp
    Source/Utils.cpp
    Source/PresetLoadingExtensionsVisitor.cpp
    Source/ProcessCommand.cpp
    Source/ListParametersCommand.cpp
    Source/Automation.cpp
    )

target_compile_definitions(Plugalyzer
    PRIVATE
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:Plugalyzer,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:Plugalyzer,JUCE_VERSION>"

    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_PLUGINHOST_VST3=1
    JUCE_PLUGINHOST_AU=1
    JUCE_PLUGINHOST_LADSPA=1
    JUCE_PLUGINHOST_LV2=1
    )

target_link_libraries(Plugalyzer
    PRIVATE
    juce::juce_core
    juce::juce_audio_basics
    juce::juce_audio_processors
    juce::juce_audio_formats
    juce::juce_audio_devices
    juce::juce_audio_utils

    CLI11::CLI11
    nlohmann_json::nlohmann_json

    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags)



endif(AUXPLUG_BUILD_PLUGALYZER_BINARY)

if(AUXPLUG_BUILD_IMPULSERESPONSE_TOOL)
	set(IMPULSERESPONSE_TOOLNAME "AuxImpulse")
	add_executable(
		${IMPULSERESPONSE_TOOLNAME}
		Automation/main.cpp
	)

target_link_libraries(${IMPULSERESPONSE_TOOLNAME}
	AuxPort
)

target_include_directories(${IMPULSERESPONSE_TOOLNAME} PUBLIC "${auxport_SOURCE_DIR}/AuxPort")

endif(AUXPLUG_BUILD_IMPULSERESPONSE_TOOL)





