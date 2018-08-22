#
#

[Defines]
    DSC_SPECIFICATION              = 0x00010005
    PLATFORM_NAME                  = HelloFile
    PLATFORM_GUID                  = 12a015e7-a283-490a-8200-ab261adaea52
    PLATFORM_VERSION               = 0.01
    OUTPUT_DIRECTORY               = Build/HelloFile
    SUPPORTED_ARCHITECTURES        = AARCH64
    BUILD_TARGETS                  = DEBUG|RELEASE
    SKUID_IDENTIFIER               = DEFAULT

[PcdsFixedAtBuild]
    # DEBUG_ASSERT_ENABLED    = 0x01
    # DEBUG_PRINT_ENABLED     = 0x02
    # DEBUG_CODE_ENABLED      = 0x04
    # DEBUG_ASSERT_CLEAR_MEM  = 0x08
    # DEBUG_ASSERT_BREAKPOINT = 0x10
    # DEBUG_ASSERT_DEADLOOP   = 0x20
    gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x27

    # DEBUG_INIT      0x00000001  // Initialization
    # DEBUG_WARN      0x00000002  // Warnings
    # DEBUG_LOAD      0x00000004  // Load events
    # DEBUG_FS        0x00000008  // EFI File system
    # DEBUG_POOL      0x00000010  // Alloc & Free's
    # DEBUG_PAGE      0x00000020  // Alloc & Free's
    # DEBUG_INFO      0x00000040  // Informative
    # DEBUG_DISPATCH  0x00000080  // PEI/DXE Dispatchers
    # DEBUG_VARIABLE  0x00000100  // Variable
    # DEBUG_BM        0x00000400  // Boot Manager
    # DEBUG_BLKIO     0x00001000  // BlkIo Driver
    # DEBUG_NET       0x00004000  // SNI Driver
    # DEBUG_UNDI      0x00010000  // UNDI Driver
    # DEBUG_LOADFILE  0x00020000  // UNDI Driver
    # DEBUG_EVENT     0x00080000  // Event messages
    # DEBUG_VERBOSE   0x00400000  // Verbose
    # DEBUG_ERROR     0x80000000  // Error
    # If this isn't set, the ShellLib initialisation fails an assertion, as
    # the underlying protocols haven't been configured.  We don't need shell
    # services, so we leave the library unconfigured.

[LibraryClasses]
    UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
    UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
    PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
    DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
    DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
    BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
    BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
    PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
    MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
    UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
    DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
    UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
    UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
    UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf

[LibraryClasses.AARCH64]
    ArmLib|ArmPkg/Library/ArmLib/AArch64/AArch64Lib.inf

[SkuIds]
    0|DEFAULT

[Components]
    HelloFile/Application/HelloFile/HelloFile.inf