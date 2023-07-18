// Execute as long as condition is true
while (bool_cond) {
    // bool_cond must be of type bool:
    // if (7) {} is illegal in Java!
    if (bool_cond) {
        continue;   // Goto start of inner loop
    } else {
        break;      // Exit inner loop
    }
}

for (init_expr; bool_cond; post_expr) {
    // Equivalent to {
    //     init_expr;
    //     while (bool_cond) {
    //          { block }
    //          post_expr;
    //     }
    // }  The scope of init_expr is the loop
}
