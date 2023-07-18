do {   // Do not repeat when
       // condtion becomes false.
} while (bool_cond);

switch (choice) {
    // byte, char, int, …
    case constant_integer:
        break;
    case enum_constant:
        break;
    // Since Java 7
    case "constant_string":
        break;
    default:
        break;
}

// There is actually a "tame goto":
// A break to a labled block.
