cmake_minimum_required(VERSION 3.22)
project(osux)

set(CMAKE_CXX_STANDARD 20)

#find SDL stuff...
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
#find_package(SDL2_gfx REQUIRED) # replaced by SDL2_gfx_bbc

add_compile_definitions(__COMPILER_ID__="${CMAKE_CXX_COMPILER_ID}[${CMAKE_CXX_COMPILER}]" __COMPILER_VER__="${CMAKE_CXX_COMPILER_VERSION}")

add_executable(osux src/main.cxx src/Core/Engine.cxx src/Core/Engine.hxx src/IO/Beatmap.cxx src/IO/Beatmap.hxx src/Util/StringSplit.hxx src/Entities/Osu/PlayingFieldEntity.cxx src/Entities/Osu/PlayingFieldEntity.hxx src/Entities/Osu/HitObjects/Circle.cxx src/Entities/Osu/HitObjects/Circle.hxx src/Util/Osu.hxx src/Util/Osu.cpp src/Textures.hxx src/Entities/PerformanceMeterEntity.cxx src/Entities/PerformanceMeterEntity.hxx src/Core/Entities/TextEntity.cxx src/Core/Entities/TextEntity.hxx src/IO/Logger.hxx src/Core/Components/ResourceManager.cxx src/Core/Components/ResourceManager.hxx src/include.hxx src/Core/Entity.hxx src/Core/EntityCollection.hxx src/Core/EntityCollection.cxx src/Core/Entity.cxx src/IO/Logger.cxx src/Core/Entities/WifeEntity.cxx src/Core/Entities/WifeEntity.hxx src/Core/Components/EventManager.cxx src/Core/Components/EventManager.hxx src/Entities/VolumeEntity.cxx src/Entities/VolumeEntity.hxx src/Core/Render.cxx src/Core/Render.hxx src/SDL2_gfx_bbc/SDL2_gfxPrimitives.c src/SDL2_gfx_bbc/SDL2_rotozoom.c src/Core/Scenes/Scene.cxx src/Core/Scenes/Scene.hxx src/Core/Components/SceneManager.cxx src/Core/Components/SceneManager.hxx src/Entities/Osu/HitObjects/Slider.cxx src/Entities/Osu/HitObjects/Slider.hxx src/Core/Scenes/DefaultScene.hxx src/Core/Scenes/DefaultScene.cxx src/Scenes/BeatmapScene.cxx src/Scenes/BeatmapScene.hxx src/Core/SdlExtensions.cxx src/Core/SdlExtensions.hxx src/Core/Math2D.cxx src/Core/Math2D.hxx src/Scenes/MenuScene.cxx src/Scenes/MenuScene.hxx src/Core/Entities/SpriteEntity.cxx src/Core/Entities/SpriteEntity.hxx src/IO/Config.cxx src/IO/Config.hxx src/Entities/UI/ButtonEntity.cxx src/Entities/UI/ButtonEntity.hxx src/Scenes/SettingsScene.cxx src/Scenes/SettingsScene.hxx src/Scenes/AboutScene.cxx src/Scenes/AboutScene.hxx src/Scenes/BeatmapSelectionScene.cxx src/Scenes/BeatmapSelectionScene.hxx src/IO/BeatmapCollection.cxx src/IO/BeatmapCollection.hxx)
add_custom_command(TARGET osux POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:osux>/assets/)
add_custom_command(TARGET osux POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/beatmaps/ $<TARGET_FILE_DIR:osux>/beatmaps/)

include_directories(osux ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS}) # ${SDL2_GFX_INCLUDE_DIRS}
target_link_libraries(osux -lm ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES}) # ${SDL2_GFX_LIBRARIES}
