set (MODULE_NAME "GameController")

add_library(${MODULE_NAME}
    src/GameController.cpp
)

target_include_directories(${MODULE_NAME} PUBLIC include)
