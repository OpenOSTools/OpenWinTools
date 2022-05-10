#pragma once

#include <windows.h>
#include <tchar.h>
#include "CDriverIO.h"
#include <memory>




namespace GUICLR {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// MainForm 摘要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			if (!CDriverIO::Init())
			{
				MessageBox::Show("Open driver failed", "Init", MessageBoxButtons::OK,MessageBoxIcon::Error);
			}
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	protected:
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::TabControl^ tabMain;
	private: System::Windows::Forms::TabPage^ PageProcess;




	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel2;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel3;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel4;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel5;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel6;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel7;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel8;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel9;
	private: System::Windows::Forms::ListView^ listProcess;
	private: System::Windows::Forms::ColumnHeader^ PID;
	private: System::Windows::Forms::ColumnHeader^ EPROCESS;
	private: System::Windows::Forms::ColumnHeader^ 名称;
	private: System::Windows::Forms::ColumnHeader^ CPU;
	private: System::Windows::Forms::ColumnHeader^ PPID;

	protected:



	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel3 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel4 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel5 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel6 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel7 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel8 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel9 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tabMain = (gcnew System::Windows::Forms::TabControl());
			this->PageProcess = (gcnew System::Windows::Forms::TabPage());
			this->listProcess = (gcnew System::Windows::Forms::ListView());
			this->PID = (gcnew System::Windows::Forms::ColumnHeader());
			this->EPROCESS = (gcnew System::Windows::Forms::ColumnHeader());
			this->名称 = (gcnew System::Windows::Forms::ColumnHeader());
			this->CPU = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->PPID = (gcnew System::Windows::Forms::ColumnHeader());
			this->tableLayoutPanel1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->PageProcess->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			resources->ApplyResources(this->tableLayoutPanel1, L"tableLayoutPanel1");
			this->tableLayoutPanel1->Controls->Add(this->statusStrip1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->tabMain, 0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			// 
			// statusStrip1
			// 
			resources->ApplyResources(this->statusStrip1, L"statusStrip1");
			this->statusStrip1->GripMargin = System::Windows::Forms::Padding(0);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->toolStripStatusLabel1,
					this->toolStripStatusLabel2, this->toolStripStatusLabel3, this->toolStripStatusLabel4, this->toolStripStatusLabel5, this->toolStripStatusLabel6,
					this->toolStripStatusLabel7, this->toolStripStatusLabel8, this->toolStripStatusLabel9
			});
			this->statusStrip1->Name = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			resources->ApplyResources(this->toolStripStatusLabel1, L"toolStripStatusLabel1");
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			resources->ApplyResources(this->toolStripStatusLabel2, L"toolStripStatusLabel2");
			// 
			// toolStripStatusLabel3
			// 
			this->toolStripStatusLabel3->Name = L"toolStripStatusLabel3";
			resources->ApplyResources(this->toolStripStatusLabel3, L"toolStripStatusLabel3");
			// 
			// toolStripStatusLabel4
			// 
			this->toolStripStatusLabel4->Name = L"toolStripStatusLabel4";
			resources->ApplyResources(this->toolStripStatusLabel4, L"toolStripStatusLabel4");
			// 
			// toolStripStatusLabel5
			// 
			this->toolStripStatusLabel5->Name = L"toolStripStatusLabel5";
			resources->ApplyResources(this->toolStripStatusLabel5, L"toolStripStatusLabel5");
			// 
			// toolStripStatusLabel6
			// 
			this->toolStripStatusLabel6->Name = L"toolStripStatusLabel6";
			resources->ApplyResources(this->toolStripStatusLabel6, L"toolStripStatusLabel6");
			// 
			// toolStripStatusLabel7
			// 
			this->toolStripStatusLabel7->Name = L"toolStripStatusLabel7";
			resources->ApplyResources(this->toolStripStatusLabel7, L"toolStripStatusLabel7");
			// 
			// toolStripStatusLabel8
			// 
			this->toolStripStatusLabel8->Name = L"toolStripStatusLabel8";
			resources->ApplyResources(this->toolStripStatusLabel8, L"toolStripStatusLabel8");
			// 
			// toolStripStatusLabel9
			// 
			this->toolStripStatusLabel9->Name = L"toolStripStatusLabel9";
			resources->ApplyResources(this->toolStripStatusLabel9, L"toolStripStatusLabel9");
			// 
			// tabMain
			// 
			this->tabMain->Controls->Add(this->PageProcess);
			this->tabMain->Controls->Add(this->tabPage2);
			resources->ApplyResources(this->tabMain, L"tabMain");
			this->tabMain->Name = L"tabMain";
			this->tabMain->SelectedIndex = 0;
			this->tabMain->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::tabMain_SelectedIndexChanged);
			// 
			// PageProcess
			// 
			this->PageProcess->Controls->Add(this->listProcess);
			resources->ApplyResources(this->PageProcess, L"PageProcess");
			this->PageProcess->Name = L"PageProcess";
			this->PageProcess->UseVisualStyleBackColor = true;
			// 
			// listProcess
			// 
			this->listProcess->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->PID, this->PPID,
					this->EPROCESS, this->名称, this->CPU
			});
			resources->ApplyResources(this->listProcess, L"listProcess");
			this->listProcess->FullRowSelect = true;
			this->listProcess->HideSelection = false;
			this->listProcess->Name = L"listProcess";
			this->listProcess->UseCompatibleStateImageBehavior = false;
			this->listProcess->View = System::Windows::Forms::View::Details;
			// 
			// PID
			// 
			resources->ApplyResources(this->PID, L"PID");
			// 
			// EPROCESS
			// 
			resources->ApplyResources(this->EPROCESS, L"EPROCESS");
			// 
			// 名称
			// 
			resources->ApplyResources(this->名称, L"名称");
			// 
			// CPU
			// 
			resources->ApplyResources(this->CPU, L"CPU");
			// 
			// tabPage2
			// 
			resources->ApplyResources(this->tabPage2, L"tabPage2");
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// PPID
			// 
			resources->ApplyResources(this->PPID, L"PPID");
			// 
			// MainForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MainForm";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tabMain->ResumeLayout(false);
			this->PageProcess->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void tabMain_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		switch (tabMain->SelectedIndex)
		{
		case 0:
		{
			listProcess->Items->Clear();

			ULONG	Count = 0x1000;
			std::unique_ptr<IOProcessInfo[]> buffer(new IOProcessInfo[0x1000]);
			CDriverIO::GetProcessList(&buffer[0], Count);

			for (size_t i = 0; i < Count; i++)
			{
				auto it = gcnew ListViewItem;
				
				it->Text =  ((IntPtr)buffer[i].PID).ToString();
				it->SubItems->Add(((IntPtr)buffer[i].ParentPID).ToString());
				it->SubItems->Add(((IntPtr)(buffer[i].ProcessObj)).ToString("x16"));
				it->SubItems->Add(gcnew String((const char*)buffer[i].PsName));

				listProcess->Items->Add(it);
			}

		}
			break;
		default:
			break;
		}
	}
};
}
