// windowsservice.cpp : main Windows Service project file.

#include "stdafx.h"
#include <string.h>
#include "windowsserviceWinService.h"

using namespace windowsservice;
using namespace System::Text;
using namespace System::Security::Policy;
using namespace System::Reflection;

//To install/uninstall the service, type: "windowsservice.exe -Install [-u]"
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc >= 2)
	{
		if (argv[1][0] == _T('/'))
		{
			argv[1][0] = _T('-');
		}

		if (_tcsicmp(argv[1], _T("-Install")) == 0)
		{
			array<System::String^>^ myargs = System::Environment::GetCommandLineArgs();
			array<System::String^>^ args = gcnew array<System::String^>(myargs->Length - 1);

			// Set args[0] with the full path to the assembly,
			Assembly^ assem = Assembly::GetExecutingAssembly();
			args[0] = assem->Location;

			System::Array::Copy(myargs, 2, args, 1, args->Length - 1);
			System::AppDomain^ dom = System::AppDomain::CreateDomain(L"execDom");
			System::Type^ type = System::Object::typeid;
			System::String^ path = type->Assembly->Location;
			StringBuilder^ sb = gcnew StringBuilder(path->Substring(0, path->LastIndexOf(L"\\")));
			sb->Append(L"\\InstallUtil.exe");
			Evidence^ evidence = gcnew Evidence();
			dom->ExecuteAssembly(sb->ToString(), evidence, args);
		}
	}
	else
	{
		ServiceBase::Run(gcnew windowsserviceWinService());
	}
}
