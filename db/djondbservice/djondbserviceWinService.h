#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::ServiceProcess;
using namespace System::ComponentModel;


namespace djondbservice {

	/// <summary>
	/// Summary for djondbserviceWinService
	/// </summary>
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	public ref class djondbserviceWinService : public System::ServiceProcess::ServiceBase
	{
	public:
		djondbserviceWinService()
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~djondbserviceWinService()
		{
			if (components)
			{
				delete components;
			}
		}

		/// <summary>
		/// Set things in motion so your service can do its work.
		/// </summary>
		virtual void OnStart(array<String^>^ args) override
		{
			// TODO: Add code here to start your service.
		}

		/// <summary>
		/// Stop this service.
		/// </summary>
		virtual void OnStop() override
		{
			// TODO: Add code here to perform any tear-down necessary to stop your service.
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->CanStop = true;
			this->CanPauseAndContinue = true;
			this->AutoLog = true;
			this->ServiceName = L"djondbserviceWinService";
		}
#pragma endregion
	};
}
