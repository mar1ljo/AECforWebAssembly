#include "TreeNode.cpp"
#include "bitManipulations.cpp"

AssemblyCode convertToInteger32(TreeNode node, CompilationContext context) {
  auto originalCode = node.compile(context);
  const AssemblyCode::AssemblyType i32 = AssemblyCode::AssemblyType::i32,
                                   i64 = AssemblyCode::AssemblyType::i64,
                                   f32 = AssemblyCode::AssemblyType::f32,
                                   f64 = AssemblyCode::AssemblyType::f64,
                                   null = AssemblyCode::AssemblyType::null;
  if (originalCode.assemblyType == null) {
    std::cerr
        << "Line " << node.lineNumber << ", Column " << node.columnNumber
        << ", Compiler error: Some part of the compiler attempted to convert \""
        << node.text
        << "\" to \"Integer32\", which makes no sense. This could be an "
           "internal compiler error, or there could be something semantically "
           "(though not grammatically) very wrong with your program."
        << std::endl;
    exit(1);
  }
  if (originalCode.assemblyType == i32)
    return originalCode;
  if (originalCode.assemblyType == i64)
    return AssemblyCode(
        "(i32.wrap_i64\n" + std::string(originalCode.indentBy(1)) + "\n)", i32);
  if (originalCode.assemblyType == f32)
    return AssemblyCode(
        "(i32.trunc_f32_s\n" + std::string(originalCode.indentBy(1)) + "\n)",
        i32); // Makes little sense to me (that, when converting to an integer,
              // the decimal part of the number is simply truncated), but that's
              // how it is done in the vast majority of programming languages.
  if (originalCode.assemblyType == f64)
    return AssemblyCode("(i32.trunc_f64_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        i32);
  std::cerr << "Line " << node.lineNumber << ", Column " << node.columnNumber
            << ", Compiler error: Internal compiler error, control reached the "
               "end of the \"convertToInteger32\" function!"
            << std::endl;
  exit(-1);
  return AssemblyCode("()");
}

AssemblyCode convertToInteger64(TreeNode node, CompilationContext context) {
  auto originalCode = node.compile(context);
  const AssemblyCode::AssemblyType i32 = AssemblyCode::AssemblyType::i32,
                                   i64 = AssemblyCode::AssemblyType::i64,
                                   f32 = AssemblyCode::AssemblyType::f32,
                                   f64 = AssemblyCode::AssemblyType::f64,
                                   null = AssemblyCode::AssemblyType::null;
  if (originalCode.assemblyType == null) {
    std::cerr
        << "Line " << node.lineNumber << ", Column " << node.columnNumber
        << ", Compiler error: Some part of the compiler attempted to convert \""
        << node.text
        << "\" to \"Integer64\", which makes no sense. This could be an "
           "internal compiler error, or there could be something semantically "
           "(though not grammatically) very wrong with your program."
        << std::endl;
    exit(1);
  }
  if (originalCode.assemblyType == i32)
    return AssemblyCode(
        "(i64.extend_i32_s\n" + // If you don't put "_s", JavaScript Virtual
                                // Machine is going to interpret the argument as
                                // unsigned, leading to huge positive numbers
                                // instead of negative ones.
            std::string(originalCode.indentBy(1)) + "\n)",
        i64);
  if (originalCode.assemblyType == i64)
    return originalCode;
  if (originalCode.assemblyType == f32)
    return AssemblyCode("(i64.trunc_f32_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        i64);
  if (originalCode.assemblyType == f64)
    return AssemblyCode("(i64.trunc_f64_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        i64);
  std::cerr << "Line " << node.lineNumber << ", Column " << node.columnNumber
            << ", Compiler error: Internal compiler error, control reached the "
               "end of the \"convertToInteger64\" function!"
            << std::endl;
  exit(-1);
  return AssemblyCode("()");
}

AssemblyCode convertToDecimal32(TreeNode node, CompilationContext context) {
  auto originalCode = node.compile(context);
  const AssemblyCode::AssemblyType i32 = AssemblyCode::AssemblyType::i32,
                                   i64 = AssemblyCode::AssemblyType::i64,
                                   f32 = AssemblyCode::AssemblyType::f32,
                                   f64 = AssemblyCode::AssemblyType::f64,
                                   null = AssemblyCode::AssemblyType::null;
  if (originalCode.assemblyType == null) {
    std::cerr
        << "Line " << node.lineNumber << ", Column " << node.columnNumber
        << ", Compiler error: Some part of the compiler attempted to convert \""
        << node.text
        << "\" to \"Decimal32\", which makes no sense. This could be an "
           "internal compiler error, or there could be something semantically "
           "(though not grammatically) very wrong with your program."
        << std::endl;
    exit(1);
  }
  if (originalCode.assemblyType == i32)
    return AssemblyCode(
        "(f32.convert_i32_s\n" + // Again, those who designed JavaScript Virtual
                                 // Machine had a weird idea that integers
                                 // should be unsigned unless somebody makes
                                 // them explicitly signed via "_s".
            std::string(originalCode.indentBy(1)) + "\n)",
        f32);
  if (originalCode.assemblyType == i64)
    return AssemblyCode("(f32.convert_i64_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        f32);
  if (originalCode.assemblyType == f32)
    return originalCode;
  if (originalCode.assemblyType == f64)
    return AssemblyCode("(f32.demote_f64\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        f32);
  std::cerr << "Line " << node.lineNumber << ", Column " << node.columnNumber
            << ", Compiler error: Internal compiler error, control reached the "
               "end of the \"convertToDecimal32\" function!"
            << std::endl;
  exit(-1);
  return AssemblyCode("()");
}

AssemblyCode convertToDecimal64(TreeNode node, CompilationContext context) {
  auto originalCode = node.compile(context);
  const AssemblyCode::AssemblyType i32 = AssemblyCode::AssemblyType::i32,
                                   i64 = AssemblyCode::AssemblyType::i64,
                                   f32 = AssemblyCode::AssemblyType::f32,
                                   f64 = AssemblyCode::AssemblyType::f64,
                                   null = AssemblyCode::AssemblyType::null;
  if (originalCode.assemblyType == null) {
    std::cerr
        << "Line " << node.lineNumber << ", Column " << node.columnNumber
        << ", Compiler error: Some part of the compiler attempted to convert \""
        << node.text
        << "\" to \"Decimal64\", which makes no sense. This could be an "
           "internal compiler error, or there could be something semantically "
           "(though not grammatically) very wrong with your program."
        << std::endl;
    exit(1);
  }
  if (originalCode.assemblyType == i32)
    return AssemblyCode("(f64.convert_i32_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        f64);
  if (originalCode.assemblyType == i64)
    return AssemblyCode("(f64.convert_i64_s\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        f64);
  if (originalCode.assemblyType == f32)
    return AssemblyCode("(f64.promote_f32\n" +
                            std::string(originalCode.indentBy(1)) + "\n)",
                        f64);
  if (originalCode.assemblyType == f64)
    return originalCode;
  std::cerr << "Line " << node.lineNumber << ", Column " << node.columnNumber
            << ", Compiler error: Internal compiler error, control reached the "
               "end of the \"convertToDecimal64\" function!"
            << std::endl;
  exit(-1);
  return AssemblyCode("()");
}

AssemblyCode convertTo(TreeNode node, std::string type,
                       CompilationContext context) {
  if (type == "Character" or type == "Integer16" or type == "Integer32" or
      std::regex_search(
          type,
          std::regex(
              "Pointer$"))) // When, in JavaScript Virtual Machine, you can't
                            // push types of less than 4 bytes (32 bits) onto
                            // the system stack, you need to convert those to
                            // Integer32 (i32). Well, makes slightly more sense
                            // than the way it is in 64-bit x86 assembly, where
                            // you can put 16-bit values and 64-bit values onto
                            // the system stack, but you can't put 32-bit
                            // values.
    return convertToInteger32(node, context);
  if (type == "Integer64")
    return convertToInteger64(node, context);
  if (type == "Decimal32")
    return convertToDecimal32(node, context);
  if (type == "Decimal64")
    return convertToDecimal64(node, context);
  std::cerr << "Line " << node.lineNumber << ", Column " << node.columnNumber
            << ", Compiler error: Some part of the compiler attempted to get "
               "the assembly code for converting \""
            << node.text << "\" into the type \"" << type
            << "\", which doesn't make sense. This could be an internal "
               "compiler error, or there could be something semantically "
               "(though not grammatically) very wrong with your program."
            << std::endl;
  exit(-1);
  return AssemblyCode("()");
}

std::string getStrongerType(int, int, std::string,
                            std::string); // When C++ doesn't support function
                                          // hoisting, like JavaScript does.

AssemblyCode TreeNode::compile(CompilationContext context) {
  std::string typeOfTheCurrentNode = getType(context);
  AssemblyCode::AssemblyType returnType =
      mappingOfAECTypesToWebAssemblyTypes[typeOfTheCurrentNode];
  auto iteratorOfTheCurrentFunction =
      std::find_if(context.functions.begin(), context.functions.end(),
                   [=](function someFunction) {
                     return someFunction.name == context.currentFunctionName;
                   });
  if (iteratorOfTheCurrentFunction == context.functions.end()) {
    std::cerr
        << "Line " << lineNumber << ", Column " << columnNumber
        << ", Internal compiler error: The \"compile(CompilationContext)\" "
           "function was called without setting the current function name, "
           "aborting compilation (or else the compiler will segfault)!"
        << std::endl;
    exit(1);
  }
  function currentFunction = *iteratorOfTheCurrentFunction;
  std::string assembly;
  if (text == "Does" or text == "Then" or text == "Loop" or
      text == "Else") // Blocks of code are stored by the parser as child nodes
                      // of "Does", "Then", "Else" and "Loop".
  {
    if (text != "Does")
      context.stackSizeOfThisScope =
          0; //"TreeRootNode" is supposed to set up the arguments in the scope
             // before passing the recursion onto the "Does" node.
    for (auto childNode : children) {
      if (childNode.text == "Nothing")
        continue;
      assembly += std::string(childNode.compile(context)) + "\n";
    }
    assembly += "(global.set $stack_pointer (i32.sub (global.get "
                "$stack_pointer) (i32.const " +
                std::to_string(context.stackSizeOfThisScope) + ")))";
  } else if (text.front() == '"')
    assembly += "(i32.const " + std::to_string(context.globalVariables[text]) +
                ") ;;Pointer to " + text;
  else if (context.variableTypes.count(text)) {
    if (typeOfTheCurrentNode == "Character")
      assembly +=
          "(i32.load8_s\n" + compileAPointer(context).indentBy(1) + "\n)";
    else if (typeOfTheCurrentNode == "Integer16")
      assembly +=
          "(i32.load16_s\n" + compileAPointer(context).indentBy(1) + "\n)";
    else if (typeOfTheCurrentNode == "Integer32" or
             std::regex_search(typeOfTheCurrentNode, std::regex("Pointer$")))
      assembly += "(i32.load\n" + compileAPointer(context).indentBy(1) + "\n)";
    else if (typeOfTheCurrentNode == "Integer64")
      assembly += "(i64.load\n" + compileAPointer(context).indentBy(1) + "\n)";
    else if (typeOfTheCurrentNode == "Decimal32")
      assembly += "(f32.load\n" + compileAPointer(context).indentBy(1) + "\n)";
    else if (typeOfTheCurrentNode == "Decimal64")
      assembly += "(f64.load\n" + compileAPointer(context).indentBy(1) + "\n)";
    else {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Internal compiler error: Compiler got into a forbidden "
                   "state while compiling the token \""
                << text << "\", aborting the compilation!" << std::endl;
      exit(1);
    }
  } else if (std::regex_match(text,
                              std::regex("(^\\d+$)|(^0x(\\d|[a-f]|[A-F])+$)")))
    assembly += "(i64.const " + text + ")";
  else if (std::regex_match(text, std::regex("^\\d+\\.\\d*$")))
    assembly += "(f64.const " + text + ")";
  else if (text == "Return") {
    assembly += "(return";
    if (currentFunction.returnType == "Nothing")
      assembly += ")";
    else {
      if (children.empty()) {
        std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                  << ", Compiler error: It's not specified what to return from "
                     "a function that's supposed to return \""
                  << currentFunction.returnType
                  << "\", aborting the compilation (or else the compiler will "
                     "segfault)!"
                  << std::endl;
        exit(1);
      }
      assembly += "\n" +
                  convertTo(children[0], currentFunction.returnType, context)
                      .indentBy(1) +
                  "\n)";
    }
  } else if (text == "+") {
    if (std::regex_search(children[1].getType(context), std::regex("Pointer$")))
      std::iter_swap(children.begin(), children.begin() + 1);
    std::string firstType = children[0].getType(context);
    std::string secondType = children[1].getType(context);
    if (std::regex_search(
            firstType,
            std::regex(
                "Pointer$"))) // Multiply the second operand by the numbers of
                              // bytes the data type that the pointer points to
                              // takes. That is, be compatible with pointers in
                              // C and C++, rather than with pointers in
                              // Assembly (which allows unaligned access).
      assembly += "(i32.add\n" +
                  std::string(children[0].compile(context).indentBy(1)) +
                  "\n\t(i32.mul (i32.const " +
                  std::to_string(basicDataTypeSizes[firstType.substr(
                      0, firstType.size() - std::string("Pointer").size())]) +
                  ")\n" + convertToInteger32(children[1], context).indentBy(2) +
                  "\n\t\t)\n\t)\n)";
    else
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[returnType] + ".add\n" +
          convertTo(children[0], typeOfTheCurrentNode, context).indentBy(1) +
          "\n" +
          convertTo(children[1], typeOfTheCurrentNode, context).indentBy(1) +
          "\n)";
  } else if (text == "-") {
    std::string firstType = children[0].getType(context);
    std::string secondType = children[1].getType(context);
    if (!std::regex_search(firstType, std::regex("Pointer$")) and
        std::regex_search(secondType, std::regex("Pointer$"))) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: What exactly does it mean to subtract a "
                   "pointer from a number? Aborting the compilation!"
                << std::endl;
      exit(1);
    } else if (std::regex_search(firstType, std::regex("Pointer$")) and
               std::regex_search(
                   secondType,
                   std::regex("Pointer$"))) // Subtract two pointers as if they
                                            // were two Integer32s.
      assembly += "(i32.sub\n" + children[0].compile(context).indentBy(1) +
                  "\n" + children[1].compile(context).indentBy(1) + "\n)";
    else if (std::regex_search(firstType, std::regex("Pointer$")) and
             !std::regex_search(secondType, std::regex("Pointer$")))
      assembly += "(i32.sub\n" + children[0].compile(context).indentBy(1) +
                  "\n\t(i32.mul (i32.const " +
                  std::to_string(basicDataTypeSizes[firstType.substr(
                      0, firstType.size() - std::string("Pointer").size())]) +
                  ")\n" + children[1].compile(context).indentBy(2) +
                  "\n\t\t)\n\t)\n)";
    else
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[returnType] + ".sub\n" +
          convertTo(children[0], typeOfTheCurrentNode, context).indentBy(1) +
          "\n" +
          convertTo(children[1], typeOfTheCurrentNode, context).indentBy(1) +
          "\n)";
  } else if (text == "*")
    assembly +=
        "(" + stringRepresentationOfWebAssemblyType[returnType] + ".mul\n" +
        convertTo(children[0], typeOfTheCurrentNode, context).indentBy(1) +
        "\n" +
        convertTo(children[1], typeOfTheCurrentNode, context).indentBy(1) +
        "\n)";
  else if (text == "/") {
    if (returnType == AssemblyCode::AssemblyType::i32 or
        returnType == AssemblyCode::AssemblyType::i64)
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[returnType] + ".div_s\n" +
          convertTo(children[0], typeOfTheCurrentNode, context).indentBy(1) +
          "\n" +
          convertTo(children[1], typeOfTheCurrentNode, context).indentBy(1) +
          "\n)";
    else
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[returnType] + ".div\n" +
          convertTo(children[0], typeOfTheCurrentNode, context).indentBy(1) +
          "\n" +
          convertTo(children[1], typeOfTheCurrentNode, context).indentBy(1) +
          "\n)";
  } else if (text == "<" or text == ">") {
    std::string firstType = children[0].getType(context);
    std::string secondType = children[1].getType(context);
    std::string strongerType;
    if (std::regex_search(firstType, std::regex("Pointer$")) and
        std::regex_search(secondType, std::regex("Pointer$")))
      strongerType =
          "Integer32"; // Let's allow people to shoot themselves in the foot by
                       // comparing pointers of different types.
    else
      strongerType =
          getStrongerType(lineNumber, columnNumber, firstType, secondType);
    AssemblyCode::AssemblyType assemblyType =
        mappingOfAECTypesToWebAssemblyTypes[strongerType];
    if (assemblyType == AssemblyCode::AssemblyType::i32 or
        assemblyType == AssemblyCode::AssemblyType::i64)
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[assemblyType] +
          (text == "<" ? ".lt_s\n" : ".gt_s\n") +
          convertTo(children[0], strongerType, context).indentBy(1) + "\n" +
          convertTo(children[1], strongerType, context).indentBy(1) + "\n)";
    else
      assembly +=
          "(" + stringRepresentationOfWebAssemblyType[assemblyType] +
          (text == "<" ? ".lt\n" : ".gt\n") +
          convertTo(children[0], strongerType, context).indentBy(1) + "\n" +
          convertTo(children[1], strongerType, context).indentBy(1) + "\n)";
  } else if (text == "=") {
    std::string firstType = children[0].getType(context);
    std::string secondType = children[1].getType(context);
    std::string strongerType;
    if (std::regex_search(firstType, std::regex("Pointer$")) and
        std::regex_search(secondType, std::regex("Pointer$")))
      strongerType = "Integer32";
    else
      strongerType =
          getStrongerType(lineNumber, columnNumber, firstType, secondType);
    AssemblyCode::AssemblyType assemblyType =
        mappingOfAECTypesToWebAssemblyTypes[strongerType];
    assembly +=
        "(" + stringRepresentationOfWebAssemblyType[assemblyType] + ".eq\n" +
        convertTo(children[0], strongerType, context).indentBy(1) + "\n" +
        convertTo(children[1], strongerType, context).indentBy(1) + "\n)";
  } else if (text == "?:")
    assembly +=
        "(if (result " + stringRepresentationOfWebAssemblyType[returnType] +
        ")\n" + convertToInteger32(children[0], context).indentBy(1) +
        "\n\t(then\n" +
        convertTo(children[1], typeOfTheCurrentNode, context).indentBy(2) +
        "\n\t)\n\t(else\n" +
        convertTo(children[2], typeOfTheCurrentNode, context).indentBy(2) +
        "\n\t)\n)";
  else if (text == "not(")
    assembly += "(i32.xor (i32.const 0xffffffff)\n" +
                convertToInteger32(children[0], context).indentBy(1) + "\n)";
  else if (text.back() == '(' and
           basicDataTypeSizes.count(
               text.substr(0, text.size() - 1))) // The casting operator.
    assembly +=
        convertTo(children[0], text.substr(0, text.size() - 1), context);
  else {
    std::cerr << "Line " << lineNumber << ", Column " << columnNumber
              << ", Compiler error: No rule to compile the token \"" << text
              << "\", quitting now!" << std::endl;
    exit(1);
  }
  return AssemblyCode(assembly, returnType);
}

AssemblyCode TreeNode::compileAPointer(CompilationContext context) {
  if (text == "ValueAt(")
    return children[0].compile(context);
  if (context.localVariables.count(text) and text.back() != '[')
    return AssemblyCode(
        "(i32.sub\n\t(global.get $stack_pointer)\n\t(i32.const " +
            std::to_string(context.localVariables[text]) + ") ;;" + text +
            "\n)",
        AssemblyCode::AssemblyType::i32);
  if (context.localVariables.count(text) and text.back() == '[') {
    if (children.empty()) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The array \""
                << text.substr(0, text.size() - 1)
                << "\" has no index in the AST. Aborting the compilation, or "
                   "else the compiler will segfault!"
                << std::endl;
      exit(1);
    }
    return AssemblyCode(
        "(i32.add\n\t(i32.sub\n\t\t(global.get "
        "$stack_pointer)\n\t\t(i32.const " +
            std::to_string(context.localVariables[text]) + ") ;;" + text +
            "\n\t)\n)" +
            std::string(convertToInteger32(children[0], context).indentBy(1)) +
            "\n)",
        AssemblyCode::AssemblyType::i32);
  }
  if (context.globalVariables.count(text) and text.back() != '[')
    return AssemblyCode("(i32.const " +
                            std::to_string(context.globalVariables[text]) +
                            ") ;;" + text,
                        AssemblyCode::AssemblyType::i32);
  if (context.globalVariables.count(text) and text.back() == '[') {
    if (children.empty()) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The array \""
                << text.substr(0, text.size() - 1)
                << "\" has no index in the AST. Aborting the compilation, or "
                   "else the compiler will segfault!"
                << std::endl;
      exit(1);
    }
    return AssemblyCode(
        "(i32.add\n\t(i32.const " +
            std::to_string(context.globalVariables[text]) + ") ;;" + text +
            "\n" +
            std::string(convertToInteger32(children[0], context).indentBy(1)) +
            "\n)",
        AssemblyCode::AssemblyType::i32);
  }
  std::cerr << "Line " << lineNumber << ", Column " << columnNumber
            << ", Compiler error: Some part of the compiler attempted to get "
               "the assembly of the pointer to \""
            << text
            << "\", which makes no sense. This could be an internal compiler "
               "error, or there could be something semantically (though not "
               "grammatically) very wrong with your program."
            << std::endl;
  exit(1);
  return AssemblyCode("()");
}

std::string getStrongerType(int lineNumber, int columnNumber,
                            std::string firstType, std::string secondType) {
  if (firstType == "Nothing" or secondType == "Nothing") {
    std::cerr << "Line " << lineNumber << ", Column " << columnNumber
              << ", Compiler error: Can't add, subtract, multiply or divide "
                 "with something of the type \"Nothing\"!";
    exit(1);
  }
  if (std::regex_search(firstType, std::regex("Pointer$")) and
      !std::regex_search(secondType, std::regex("Pointer$")))
    return firstType;
  if (std::regex_search(secondType, std::regex("Pointer$")) and
      !std::regex_search(firstType, std::regex("Pointer$")))
    return secondType;
  if (std::regex_search(firstType, std::regex("Pointer$")) and
      std::regex_search(secondType, std::regex("Pointer$"))) {
    std::cerr
        << "Line " << lineNumber << ", Column " << columnNumber
        << ", Compiler error: Can't add, multiply or divide two pointers!";
  }
  if (firstType == "Decimal64" or secondType == "Decimal64")
    return "Decimal64";
  if (firstType == "Decimal32" or secondType == "Decimal32")
    return "Decimal32";
  if (firstType == "Integer64" or secondType == "Integer64")
    return "Integer64";
  if (firstType == "Integer32" or secondType == "Integer32")
    return "Integer32";
  if (firstType == "Integer16" or secondType == "Integer16")
    return "Integer16";
  return firstType;
}

std::string TreeNode::getType(CompilationContext context) {
  if (std::regex_match(text, std::regex("(^\\d+$)|(^0x(\\d|[a-f]|[A-F])+$)")))
    return "Integer64";
  if (std::regex_match(text, std::regex("^\\d+\\.\\d*$")))
    return "Decimal64";
  if (text == "AddressOf(") {
    if (children.empty()) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: \"AddressOf\" is without the argument!"
                << std::endl;
      exit(1);
    }
    if (children.size() > 1) {
      std::cerr
          << "Line " << lineNumber << ", Column " << columnNumber
          << ", Compiler error: Can't take the address of multiple variables!"
          << std::endl;
      exit(1);
    }
    if (children[0].getType(context) == "Nothing") {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: \"AddressOf\" has an argument of type "
                   "\"Nothing\"!"
                << std::endl;
      exit(1);
    }
    return children[0].getType(context) + "Pointer";
  }
  if (text == "ValueAt(") {
    if (children.empty()) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: \"ValueAt\" is without the argument!"
                << std::endl;
      exit(1);
    }
    if (children.size() > 1) {
      std::cerr
          << "Line " << lineNumber << ", Column " << columnNumber
          << ", Compiler error: Can't dereference multiple variables at once!"
          << std::endl;
      exit(1);
    }
    if (std::regex_search(text, std::regex("Pointer$")) == false) {
      std::cerr
          << "Line " << lineNumber << ", Column " << columnNumber
          << ", Compiler error: The argument to \"ValueAt\" is not a pointer!"
          << std::endl;
      exit(1);
    }
  }
  if (context.variableTypes.count(text))
    return context.variableTypes[text];
  if (text == "and" or text == "or" or text == "<" or text == ">" or
      text == "=" or text == "not(") {
    if (children.empty()) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The operator \"" << text
                << "\" has no operands. Aborting the compilation (or else we "
                   "will segfault)!"
                << std::endl;
      exit(1);
    }
    if (children.size() < 2 and text != "not(") {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The binary operator \"" << text
                << "\" has less than two operands. Aborting the compilation "
                   "(or else we will segfault)!"
                << std::endl;
      exit(1);
    }
    return "Integer32"; // Because "if" and "br_if" in WebAssembly expect a
                        // "i32", so let's adapt to that.
  }
  if (text == "mod(") {
    if (children.size() != 2) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: \"mod(\" operator requires two integer "
                   "arguments!"
                << std::endl;
      exit(1);
    }
    if (std::regex_search(children[0].getType(context),
                          std::regex("^Decimal")) or
        std::regex_search(children[1].getType(context),
                          std::regex("^Decimal"))) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: Unfortunately, WebAssembly (unlike x86 "
                   "assembly) doesn't support computing remaining of division "
                   "of decimal numbers, so we can't support that either "
                   "outside of compile-time constants."
                << std::endl;
      exit(1);
    }
    return getStrongerType(lineNumber, columnNumber,
                           children[0].getType(context),
                           children[1].getType(context));
  }
  if (text == "If" or text == "Then" or text == "Else" or text == "While" or
      text == "Loop" or text == "Does" or
      text == "Return") // Or else the compiler will claim those
                        // tokens are undeclared variables.
    return "Nothing";
  if (std::regex_match(text, std::regex("^(_|[a-z]|[A-Z])\\w*\\[?"))) {
    std::cerr << "Line " << lineNumber << ", Column " << columnNumber
              << ", Compiler error: The variable name \"" << text
              << "\" is not declared!" << std::endl;
    exit(1);
  }
  if (text == "+" or text == "*" or text == "/") {
    if (children.size() != 2) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The binary operator \"" << text
                << "\" doesn't have exactly two operands. Aborting the "
                   "compilation (or else we will segfault)!"
                << std::endl;
      exit(1);
    }
    return getStrongerType(lineNumber, columnNumber,
                           children[0].getType(context),
                           children[1].getType(context));
  }
  if (text == "-") {
    if (children.size() != 2) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The binary operator \"" << text
                << "\" doesn't have exactly two operands. Aborting the "
                   "compilation (or else we will segfault)!"
                << std::endl;
      exit(1);
    }
    if (std::regex_search(children[0].getType(context),
                          std::regex("Pointer$")) and
        std::regex_search(children[1].getType(context), std::regex("Pointer$")))
      return "Integer32"; // Difference between pointers is an integer of the
                          // same size as the pointers (32-bit).
    return getStrongerType(lineNumber, columnNumber,
                           children[0].getType(context),
                           children[1].getType(context));
  }
  if (text == ":=") {
    if (children.size() < 2) {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: The assignment operator \":=\" has less "
                   "than two operands. Aborting the compilation, or else the "
                   "compiler will segfault."
                << std::endl;
      exit(1);
    }
    if (children[1].getType(context) == "Nothing") {
      std::cerr << "Line " << lineNumber << ", Column " << columnNumber
                << ", Compiler error: Attempting to assign something of the "
                   "type \"Nothing\" to a variable. Aborting the compilation!"
                << std::endl;
    }
    return children[0].getType(context);
  }
  auto potentialFunction =
      std::find_if(context.functions.begin(), context.functions.end(),
                   [=](function fn) { return fn.name == text; });
  if (potentialFunction != context.functions.end())
    return potentialFunction->returnType;
  if (text.back() == '(' and
      basicDataTypeSizes.count(text.substr(0, text.size() - 1))) // Casting
    return text.substr(0, text.size() - 1);
  if (text.back() == '(') {
    std::cerr << "Line " << lineNumber << ", Column " << columnNumber
              << ", Compiler error: Function \"" << text
              << "\" is not declared!" << std::endl;
    exit(1);
  }
  if (text == "?:")
    return getStrongerType(lineNumber, columnNumber,
                           children[1].getType(context),
                           children[2].getType(context));
  return "Nothing";
}
