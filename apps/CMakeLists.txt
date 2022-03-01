add_executable(tictactoe-evaluator main.cc)
target_compile_features(tictactoe-evaluator PRIVATE cxx_std_17)
target_link_libraries(tictactoe-evaluator PRIVATE tictactoe)