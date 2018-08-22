
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Protocol/SimpleFileSystem.h>

//extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
//gEfiSimpleFileSystemProtocolGuid就是协议的GUID

EFI_STATUS EFIAPI GetString(IN EFI_SYSTEM_TABLE *gST, CHAR16 *Str)
{
    UINTN Index1, Index2 = 0;
    EFI_STATUS Status;
    EFI_INPUT_KEY key;

    while (EFI_SUCCESS == (Status = gST->BootServices->WaitForEvent(1, &(gST->ConIn->WaitForKey), &Index1)))
    {
        gST->ConIn->ReadKeyStroke(gST->ConIn, &key);

        if (key.UnicodeChar == 13)
        {
            Str[Index2] = 0;
            break;
        }

        if (key.UnicodeChar != 8)
        {
            Str[Index2] = key.UnicodeChar;
            ++Index2;
            Print(L"%c", key.UnicodeChar);
        }
        else
        {
            if (Index2 > 0)
            {
                Str[Index2] = 0;
                --Index2;
                Print(L"\b");
            }
        }
    }

    Print(L"\n");

    return Status;
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;                    //用来接收函数返回值，判断函数执行情况
    UINTN HandleCount;
    INTN HandleIndex = 0;    //HandleCount表示个数
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Sfs; //将协议加载到Sfs上
    EFI_HANDLE *Files = NULL;             //Files用来接收容器
    EFI_FILE_PROTOCOL *Root;              //Root是用来打开卷的
    EFI_FILE_PROTOCOL *file;              //file是用来读取文件的
    UINTN FileSize = 512, i;              //FileSize用来表示前后读取大小
    UINT8 FileBuffer[512];                //存放读取到的文件数据
    CHAR16 FileName[100];                 //获取文件名

    Print(L"Input FileName: \n");
    GetString(SystemTable, FileName);
    Print(L"Get FileName: %s\n", FileName);

    //找到所有提供 EFI_SIMPLE_FILE_SYSTEM_PROTOCOL 的控制器
    //将控制器s 以数组形式存放在Files中，Files用来接收，HandleCount表示个数
    Print(L"LocateHandleBuffer!\n");
    Status = SystemTable->BootServices->LocateHandleBuffer(
        ByProtocol,
        &gEfiSimpleFileSystemProtocolGuid,
        NULL,
        &HandleCount,
        &Files);

    if (!EFI_ERROR(Status))
    {
        Print(L"==successed to find %d controllers==\n", HandleCount);

        for (HandleIndex = HandleCount - 1; HandleIndex > -1; --HandleIndex)
        {
            // 打开EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
            //将协议加载到Sfs上，这样Sfs才能打开卷
            //    Status = SystemTable->BootServices->HandleProtocol(
            //     Files[HandleIndex],
            //     &gEfiSimpleFileSystemProtocolGuid,
            //     (VOID**)&Sfs);

            Print(L"OpenProtocol: EFI_SIMPLE_FILE_SYSTEM_PROTOCOL\n");
            Status = SystemTable->BootServices->OpenProtocol(
                Files[HandleIndex],
                &gEfiSimpleFileSystemProtocolGuid,
                (VOID **)&Sfs,
                ImageHandle,
                NULL,
                EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
            Print(L"OpenProtocol: %s\n", Status == EFI_SUCCESS ? L"Successed" : L"Failed");
            Print(L"sfs addr is 0x%016lx\n", &Sfs);
            Print(L"sfs->Revision is 0x%016lx\n", Sfs->Revision);

            if (Status == EFI_SUCCESS)
            {
                //uefi说明文档中有说明：要先OpenVolume打开卷，然后读取文件
                //Sfs是用来打开卷的，Root是用来打开卷的
                Print(L"Calling sfs->OpenVolume: 0x%016lx\n", Sfs->OpenVolume);
                Status = Sfs->OpenVolume(Sfs, &Root);
                Print(L"Call return: %s\n", Status == EFI_SUCCESS ? L"Successed" : L"Failed");

                if (Status == EFI_SUCCESS)
                {
                    Print(L"==controller %d successed to open the volume==\n", HandleIndex);

                    //打开文件，Root是用来打开文件的，file是用来读取文件的
                    Status = Root->Open(Root, &file, FileName, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);

                    if (Status == EFI_SUCCESS)
                    {
                        Print(L"==controller %d successed to open the file : %s==\n", HandleIndex, FileName);

                        //读取文件，file是用来读取文件的，FileSize用来表示前后读取大小
                        Status = file->Read(file, &FileSize, (VOID *)FileBuffer);

                        if (!EFI_ERROR(Status))
                        {
                            Print(L"==successed  to read the file==\n");
                            for (i = 0; i < FileSize; ++i)
                            {
                                Print(L"%c", FileBuffer[i]);
                            }
                            Print(L"\n==read over==\n");

                            //return EFI_SUCCESS;
                        }
                        else
                        {
                            Print(L"!!failed to read the file!!\n");
                        }
                    }
                    else
                    {
                        Print(L"!!controller %d failed to open the file : %s!!\n", HandleIndex, FileName);
                    }
                }
            }

            Status = SystemTable->BootServices->CloseProtocol(
                Files[HandleIndex],
                &gEfiSimpleFileSystemProtocolGuid,
                ImageHandle,
                NULL);

            if (Status == EFI_SUCCESS)
            {
                Print(L"==Successed to close the protocol==\n");
            }
            else
            {
                Print(L"!!Failed to close the protocol!!\n");
            }

            Print(L"== %d traverse over==\n", HandleCount - HandleIndex);
        }
    }
    Print(L"==program over==\n");
    return EFI_SUCCESS;
}
