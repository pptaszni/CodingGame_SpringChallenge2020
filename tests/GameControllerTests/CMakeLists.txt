add_executable(ut-gamecontroller
  main.cpp
  GameControllerTests.cpp
)
target_link_libraries(ut-gamecontroller
  gmock
  GameController
)
add_test(GameControllerTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ut-gamecontroller)
