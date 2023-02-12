add_llvm_component_library(LLVMfox32Desc
  fox32InstPrinter.cpp
  fox32MCAsmInfo.cpp
  fox32MCTargetDesc.cpp
  fox32BaseInfo.cpp

  LINK_COMPONENTS
  MC
  fox32Info
  Support

  ADD_TO_COMPONENT
  fox32
  )
