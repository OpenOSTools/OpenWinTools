
namespace GUI_WinForm
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.ProcessListMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.fsafsdToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dsafToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tabControlMain = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.List_Process = new System.Windows.Forms.ListView();
            this.PID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.名称 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.用户 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CPU = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.内存 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CPU时间 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.GPU = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.路径 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.命令行 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.tabControl3 = new System.Windows.Forms.TabControl();
            this.tabPageKModule = new System.Windows.Forms.TabPage();
            this.tabPageCallback = new System.Windows.Forms.TabPage();
            this.tabPageFilter = new System.Windows.Forms.TabPage();
            this.tabPageKVar = new System.Windows.Forms.TabPage();
            this.tabPageKThread = new System.Windows.Forms.TabPage();
            this.tabPageKTimer = new System.Windows.Forms.TabPage();
            this.tabPageDPC = new System.Windows.Forms.TabPage();
            this.tabPageInterrupt = new System.Windows.Forms.TabPage();
            this.tabPageGDT = new System.Windows.Forms.TabPage();
            this.tabPageIDT = new System.Windows.Forms.TabPage();
            this.tabPagePoolTag = new System.Windows.Forms.TabPage();
            this.tabPageSSDT = new System.Windows.Forms.TabPage();
            this.tabPageSSSDT = new System.Windows.Forms.TabPage();
            this.tabPageObject = new System.Windows.Forms.TabPage();
            this.tabPageHAL = new System.Windows.Forms.TabPage();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.tabPage8 = new System.Windows.Forms.TabPage();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPageACPI = new System.Windows.Forms.TabPage();
            this.tabPageAPIC = new System.Windows.Forms.TabPage();
            this.tabPageIOAPIC = new System.Windows.Forms.TabPage();
            this.tabPagePCI = new System.Windows.Forms.TabPage();
            this.tabPageTimers = new System.Windows.Forms.TabPage();
            this.tabPageSMBUS = new System.Windows.Forms.TabPage();
            this.tabPageDIMM = new System.Windows.Forms.TabPage();
            this.tabPageCPU = new System.Windows.Forms.TabPage();
            this.tabPageIOPorts = new System.Windows.Forms.TabPage();
            this.tabPageMMIO = new System.Windows.Forms.TabPage();
            this.tabPageDMA = new System.Windows.Forms.TabPage();
            this.tabPageDisk = new System.Windows.Forms.TabPage();
            this.tabPageUSB = new System.Windows.Forms.TabPage();
            this.tabPageVideo = new System.Windows.Forms.TabPage();
            this.tabPageTPM = new System.Windows.Forms.TabPage();
            this.tabPageNIC = new System.Windows.Forms.TabPage();
            this.tabPageMonitor = new System.Windows.Forms.TabPage();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.tabPage10 = new System.Windows.Forms.TabPage();
            this.tabPage11 = new System.Windows.Forms.TabPage();
            this.tabPage12 = new System.Windows.Forms.TabPage();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel5 = new System.Windows.Forms.ToolStripStatusLabel();
            this.EPROCESS = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ProcessListMenu.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tabControlMain.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabControl3.SuspendLayout();
            this.tabPage8.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ProcessListMenu
            // 
            this.ProcessListMenu.ImageScalingSize = new System.Drawing.Size(40, 40);
            this.ProcessListMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fsafsdToolStripMenuItem,
            this.dsafToolStripMenuItem,
            this.dToolStripMenuItem});
            this.ProcessListMenu.Name = "contextMenuStrip1";
            resources.ApplyResources(this.ProcessListMenu, "ProcessListMenu");
            // 
            // fsafsdToolStripMenuItem
            // 
            this.fsafsdToolStripMenuItem.Name = "fsafsdToolStripMenuItem";
            resources.ApplyResources(this.fsafsdToolStripMenuItem, "fsafsdToolStripMenuItem");
            // 
            // dsafToolStripMenuItem
            // 
            this.dsafToolStripMenuItem.Name = "dsafToolStripMenuItem";
            resources.ApplyResources(this.dsafToolStripMenuItem, "dsafToolStripMenuItem");
            // 
            // dToolStripMenuItem
            // 
            this.dToolStripMenuItem.Name = "dToolStripMenuItem";
            resources.ApplyResources(this.dToolStripMenuItem, "dToolStripMenuItem");
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Controls.Add(this.tabControlMain, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.statusStrip1, 0, 1);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // tabControlMain
            // 
            this.tabControlMain.AllowDrop = true;
            this.tabControlMain.Controls.Add(this.tabPage1);
            this.tabControlMain.Controls.Add(this.tabPage2);
            this.tabControlMain.Controls.Add(this.tabPage3);
            this.tabControlMain.Controls.Add(this.tabPage4);
            this.tabControlMain.Controls.Add(this.tabPage5);
            this.tabControlMain.Controls.Add(this.tabPage6);
            this.tabControlMain.Controls.Add(this.tabPage7);
            this.tabControlMain.Controls.Add(this.tabPage8);
            this.tabControlMain.Controls.Add(this.tabPage9);
            this.tabControlMain.Controls.Add(this.tabPage10);
            this.tabControlMain.Controls.Add(this.tabPage11);
            this.tabControlMain.Controls.Add(this.tabPage12);
            resources.ApplyResources(this.tabControlMain, "tabControlMain");
            this.tabControlMain.Name = "tabControlMain";
            this.tabControlMain.SelectedIndex = 0;
            this.tabControlMain.SelectedIndexChanged += new System.EventHandler(this.tabControlMain_SelectedIndexChanged);
            // 
            // tabPage1
            // 
            resources.ApplyResources(this.tabPage1, "tabPage1");
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.List_Process);
            resources.ApplyResources(this.tabPage2, "tabPage2");
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // List_Process
            // 
            this.List_Process.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.List_Process.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PID,
            this.EPROCESS,
            this.名称,
            this.用户,
            this.CPU,
            this.内存,
            this.CPU时间,
            this.GPU,
            this.路径,
            this.命令行});
            this.List_Process.ContextMenuStrip = this.ProcessListMenu;
            resources.ApplyResources(this.List_Process, "List_Process");
            this.List_Process.FullRowSelect = true;
            this.List_Process.Groups.AddRange(new System.Windows.Forms.ListViewGroup[] {
            ((System.Windows.Forms.ListViewGroup)(resources.GetObject("List_Process.Groups"))),
            ((System.Windows.Forms.ListViewGroup)(resources.GetObject("List_Process.Groups1"))),
            ((System.Windows.Forms.ListViewGroup)(resources.GetObject("List_Process.Groups2"))),
            ((System.Windows.Forms.ListViewGroup)(resources.GetObject("List_Process.Groups3"))),
            ((System.Windows.Forms.ListViewGroup)(resources.GetObject("List_Process.Groups4")))});
            this.List_Process.HideSelection = false;
            this.List_Process.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            ((System.Windows.Forms.ListViewItem)(resources.GetObject("List_Process.Items")))});
            this.List_Process.Name = "List_Process";
            this.List_Process.UseCompatibleStateImageBehavior = false;
            this.List_Process.View = System.Windows.Forms.View.Details;
            // 
            // PID
            // 
            resources.ApplyResources(this.PID, "PID");
            // 
            // 名称
            // 
            resources.ApplyResources(this.名称, "名称");
            // 
            // 用户
            // 
            resources.ApplyResources(this.用户, "用户");
            // 
            // CPU
            // 
            resources.ApplyResources(this.CPU, "CPU");
            // 
            // 内存
            // 
            resources.ApplyResources(this.内存, "内存");
            // 
            // CPU时间
            // 
            resources.ApplyResources(this.CPU时间, "CPU时间");
            // 
            // GPU
            // 
            resources.ApplyResources(this.GPU, "GPU");
            // 
            // 路径
            // 
            resources.ApplyResources(this.路径, "路径");
            // 
            // 命令行
            // 
            resources.ApplyResources(this.命令行, "命令行");
            // 
            // tabPage3
            // 
            resources.ApplyResources(this.tabPage3, "tabPage3");
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.tabControl3);
            resources.ApplyResources(this.tabPage4, "tabPage4");
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // tabControl3
            // 
            this.tabControl3.Controls.Add(this.tabPageKModule);
            this.tabControl3.Controls.Add(this.tabPageCallback);
            this.tabControl3.Controls.Add(this.tabPageFilter);
            this.tabControl3.Controls.Add(this.tabPageKVar);
            this.tabControl3.Controls.Add(this.tabPageKThread);
            this.tabControl3.Controls.Add(this.tabPageKTimer);
            this.tabControl3.Controls.Add(this.tabPageDPC);
            this.tabControl3.Controls.Add(this.tabPageInterrupt);
            this.tabControl3.Controls.Add(this.tabPageGDT);
            this.tabControl3.Controls.Add(this.tabPageIDT);
            this.tabControl3.Controls.Add(this.tabPagePoolTag);
            this.tabControl3.Controls.Add(this.tabPageSSDT);
            this.tabControl3.Controls.Add(this.tabPageSSSDT);
            this.tabControl3.Controls.Add(this.tabPageObject);
            this.tabControl3.Controls.Add(this.tabPageHAL);
            resources.ApplyResources(this.tabControl3, "tabControl3");
            this.tabControl3.Name = "tabControl3";
            this.tabControl3.SelectedIndex = 0;
            // 
            // tabPageKModule
            // 
            resources.ApplyResources(this.tabPageKModule, "tabPageKModule");
            this.tabPageKModule.Name = "tabPageKModule";
            this.tabPageKModule.UseVisualStyleBackColor = true;
            // 
            // tabPageCallback
            // 
            resources.ApplyResources(this.tabPageCallback, "tabPageCallback");
            this.tabPageCallback.Name = "tabPageCallback";
            this.tabPageCallback.UseVisualStyleBackColor = true;
            // 
            // tabPageFilter
            // 
            resources.ApplyResources(this.tabPageFilter, "tabPageFilter");
            this.tabPageFilter.Name = "tabPageFilter";
            this.tabPageFilter.UseVisualStyleBackColor = true;
            // 
            // tabPageKVar
            // 
            resources.ApplyResources(this.tabPageKVar, "tabPageKVar");
            this.tabPageKVar.Name = "tabPageKVar";
            this.tabPageKVar.UseVisualStyleBackColor = true;
            // 
            // tabPageKThread
            // 
            resources.ApplyResources(this.tabPageKThread, "tabPageKThread");
            this.tabPageKThread.Name = "tabPageKThread";
            this.tabPageKThread.UseVisualStyleBackColor = true;
            // 
            // tabPageKTimer
            // 
            resources.ApplyResources(this.tabPageKTimer, "tabPageKTimer");
            this.tabPageKTimer.Name = "tabPageKTimer";
            this.tabPageKTimer.UseVisualStyleBackColor = true;
            // 
            // tabPageDPC
            // 
            resources.ApplyResources(this.tabPageDPC, "tabPageDPC");
            this.tabPageDPC.Name = "tabPageDPC";
            this.tabPageDPC.UseVisualStyleBackColor = true;
            // 
            // tabPageInterrupt
            // 
            resources.ApplyResources(this.tabPageInterrupt, "tabPageInterrupt");
            this.tabPageInterrupt.Name = "tabPageInterrupt";
            this.tabPageInterrupt.UseVisualStyleBackColor = true;
            // 
            // tabPageGDT
            // 
            resources.ApplyResources(this.tabPageGDT, "tabPageGDT");
            this.tabPageGDT.Name = "tabPageGDT";
            this.tabPageGDT.UseVisualStyleBackColor = true;
            // 
            // tabPageIDT
            // 
            resources.ApplyResources(this.tabPageIDT, "tabPageIDT");
            this.tabPageIDT.Name = "tabPageIDT";
            this.tabPageIDT.UseVisualStyleBackColor = true;
            // 
            // tabPagePoolTag
            // 
            resources.ApplyResources(this.tabPagePoolTag, "tabPagePoolTag");
            this.tabPagePoolTag.Name = "tabPagePoolTag";
            this.tabPagePoolTag.UseVisualStyleBackColor = true;
            // 
            // tabPageSSDT
            // 
            resources.ApplyResources(this.tabPageSSDT, "tabPageSSDT");
            this.tabPageSSDT.Name = "tabPageSSDT";
            this.tabPageSSDT.UseVisualStyleBackColor = true;
            // 
            // tabPageSSSDT
            // 
            resources.ApplyResources(this.tabPageSSSDT, "tabPageSSSDT");
            this.tabPageSSSDT.Name = "tabPageSSSDT";
            this.tabPageSSSDT.UseVisualStyleBackColor = true;
            // 
            // tabPageObject
            // 
            resources.ApplyResources(this.tabPageObject, "tabPageObject");
            this.tabPageObject.Name = "tabPageObject";
            this.tabPageObject.UseVisualStyleBackColor = true;
            // 
            // tabPageHAL
            // 
            resources.ApplyResources(this.tabPageHAL, "tabPageHAL");
            this.tabPageHAL.Name = "tabPageHAL";
            this.tabPageHAL.UseVisualStyleBackColor = true;
            // 
            // tabPage5
            // 
            resources.ApplyResources(this.tabPage5, "tabPage5");
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // tabPage6
            // 
            resources.ApplyResources(this.tabPage6, "tabPage6");
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // tabPage7
            // 
            resources.ApplyResources(this.tabPage7, "tabPage7");
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.UseVisualStyleBackColor = true;
            // 
            // tabPage8
            // 
            this.tabPage8.Controls.Add(this.tabControl2);
            resources.ApplyResources(this.tabPage8, "tabPage8");
            this.tabPage8.Name = "tabPage8";
            this.tabPage8.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPageACPI);
            this.tabControl2.Controls.Add(this.tabPageAPIC);
            this.tabControl2.Controls.Add(this.tabPageIOAPIC);
            this.tabControl2.Controls.Add(this.tabPagePCI);
            this.tabControl2.Controls.Add(this.tabPageTimers);
            this.tabControl2.Controls.Add(this.tabPageSMBUS);
            this.tabControl2.Controls.Add(this.tabPageDIMM);
            this.tabControl2.Controls.Add(this.tabPageCPU);
            this.tabControl2.Controls.Add(this.tabPageIOPorts);
            this.tabControl2.Controls.Add(this.tabPageMMIO);
            this.tabControl2.Controls.Add(this.tabPageDMA);
            this.tabControl2.Controls.Add(this.tabPageDisk);
            this.tabControl2.Controls.Add(this.tabPageUSB);
            this.tabControl2.Controls.Add(this.tabPageVideo);
            this.tabControl2.Controls.Add(this.tabPageTPM);
            this.tabControl2.Controls.Add(this.tabPageNIC);
            this.tabControl2.Controls.Add(this.tabPageMonitor);
            resources.ApplyResources(this.tabControl2, "tabControl2");
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            // 
            // tabPageACPI
            // 
            resources.ApplyResources(this.tabPageACPI, "tabPageACPI");
            this.tabPageACPI.Name = "tabPageACPI";
            this.tabPageACPI.UseVisualStyleBackColor = true;
            // 
            // tabPageAPIC
            // 
            resources.ApplyResources(this.tabPageAPIC, "tabPageAPIC");
            this.tabPageAPIC.Name = "tabPageAPIC";
            this.tabPageAPIC.UseVisualStyleBackColor = true;
            // 
            // tabPageIOAPIC
            // 
            resources.ApplyResources(this.tabPageIOAPIC, "tabPageIOAPIC");
            this.tabPageIOAPIC.Name = "tabPageIOAPIC";
            this.tabPageIOAPIC.UseVisualStyleBackColor = true;
            // 
            // tabPagePCI
            // 
            resources.ApplyResources(this.tabPagePCI, "tabPagePCI");
            this.tabPagePCI.Name = "tabPagePCI";
            this.tabPagePCI.UseVisualStyleBackColor = true;
            // 
            // tabPageTimers
            // 
            resources.ApplyResources(this.tabPageTimers, "tabPageTimers");
            this.tabPageTimers.Name = "tabPageTimers";
            this.tabPageTimers.UseVisualStyleBackColor = true;
            // 
            // tabPageSMBUS
            // 
            resources.ApplyResources(this.tabPageSMBUS, "tabPageSMBUS");
            this.tabPageSMBUS.Name = "tabPageSMBUS";
            this.tabPageSMBUS.UseVisualStyleBackColor = true;
            // 
            // tabPageDIMM
            // 
            resources.ApplyResources(this.tabPageDIMM, "tabPageDIMM");
            this.tabPageDIMM.Name = "tabPageDIMM";
            this.tabPageDIMM.UseVisualStyleBackColor = true;
            // 
            // tabPageCPU
            // 
            resources.ApplyResources(this.tabPageCPU, "tabPageCPU");
            this.tabPageCPU.Name = "tabPageCPU";
            this.tabPageCPU.UseVisualStyleBackColor = true;
            // 
            // tabPageIOPorts
            // 
            resources.ApplyResources(this.tabPageIOPorts, "tabPageIOPorts");
            this.tabPageIOPorts.Name = "tabPageIOPorts";
            this.tabPageIOPorts.UseVisualStyleBackColor = true;
            // 
            // tabPageMMIO
            // 
            resources.ApplyResources(this.tabPageMMIO, "tabPageMMIO");
            this.tabPageMMIO.Name = "tabPageMMIO";
            this.tabPageMMIO.UseVisualStyleBackColor = true;
            // 
            // tabPageDMA
            // 
            resources.ApplyResources(this.tabPageDMA, "tabPageDMA");
            this.tabPageDMA.Name = "tabPageDMA";
            this.tabPageDMA.UseVisualStyleBackColor = true;
            // 
            // tabPageDisk
            // 
            resources.ApplyResources(this.tabPageDisk, "tabPageDisk");
            this.tabPageDisk.Name = "tabPageDisk";
            this.tabPageDisk.UseVisualStyleBackColor = true;
            // 
            // tabPageUSB
            // 
            resources.ApplyResources(this.tabPageUSB, "tabPageUSB");
            this.tabPageUSB.Name = "tabPageUSB";
            this.tabPageUSB.UseVisualStyleBackColor = true;
            // 
            // tabPageVideo
            // 
            resources.ApplyResources(this.tabPageVideo, "tabPageVideo");
            this.tabPageVideo.Name = "tabPageVideo";
            this.tabPageVideo.UseVisualStyleBackColor = true;
            // 
            // tabPageTPM
            // 
            resources.ApplyResources(this.tabPageTPM, "tabPageTPM");
            this.tabPageTPM.Name = "tabPageTPM";
            this.tabPageTPM.UseVisualStyleBackColor = true;
            // 
            // tabPageNIC
            // 
            resources.ApplyResources(this.tabPageNIC, "tabPageNIC");
            this.tabPageNIC.Name = "tabPageNIC";
            this.tabPageNIC.UseVisualStyleBackColor = true;
            // 
            // tabPageMonitor
            // 
            resources.ApplyResources(this.tabPageMonitor, "tabPageMonitor");
            this.tabPageMonitor.Name = "tabPageMonitor";
            this.tabPageMonitor.UseVisualStyleBackColor = true;
            // 
            // tabPage9
            // 
            resources.ApplyResources(this.tabPage9, "tabPage9");
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.UseVisualStyleBackColor = true;
            // 
            // tabPage10
            // 
            resources.ApplyResources(this.tabPage10, "tabPage10");
            this.tabPage10.Name = "tabPage10";
            this.tabPage10.UseVisualStyleBackColor = true;
            // 
            // tabPage11
            // 
            resources.ApplyResources(this.tabPage11, "tabPage11");
            this.tabPage11.Name = "tabPage11";
            this.tabPage11.UseVisualStyleBackColor = true;
            // 
            // tabPage12
            // 
            resources.ApplyResources(this.tabPage12, "tabPage12");
            this.tabPage12.Name = "tabPage12";
            this.tabPage12.UseVisualStyleBackColor = true;
            // 
            // statusStrip1
            // 
            this.statusStrip1.GripMargin = new System.Windows.Forms.Padding(0);
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(40, 40);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel3,
            this.toolStripStatusLabel4,
            this.toolStripStatusLabel5});
            this.statusStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Flow;
            resources.ApplyResources(this.statusStrip1, "statusStrip1");
            this.statusStrip1.Name = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            resources.ApplyResources(this.toolStripStatusLabel1, "toolStripStatusLabel1");
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            resources.ApplyResources(this.toolStripStatusLabel2, "toolStripStatusLabel2");
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            resources.ApplyResources(this.toolStripStatusLabel3, "toolStripStatusLabel3");
            // 
            // toolStripStatusLabel4
            // 
            this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
            resources.ApplyResources(this.toolStripStatusLabel4, "toolStripStatusLabel4");
            // 
            // toolStripStatusLabel5
            // 
            this.toolStripStatusLabel5.Name = "toolStripStatusLabel5";
            resources.ApplyResources(this.toolStripStatusLabel5, "toolStripStatusLabel5");
            // 
            // EPROCESS
            // 
            resources.ApplyResources(this.EPROCESS, "EPROCESS");
            // 
            // MainForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ProcessListMenu.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tabControlMain.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.tabControl3.ResumeLayout(false);
            this.tabPage8.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ContextMenuStrip ProcessListMenu;
        private System.Windows.Forms.ToolStripMenuItem fsafsdToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dsafToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TabControl tabControlMain;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ListView List_Process;
        private System.Windows.Forms.ColumnHeader PID;
        private System.Windows.Forms.ColumnHeader 名称;
        private System.Windows.Forms.ColumnHeader 用户;
        private System.Windows.Forms.ColumnHeader CPU;
        private System.Windows.Forms.ColumnHeader CPU时间;
        private System.Windows.Forms.ColumnHeader GPU;
        private System.Windows.Forms.ColumnHeader 路径;
        private System.Windows.Forms.ColumnHeader 内存;
        private System.Windows.Forms.ColumnHeader 命令行;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.TabControl tabControl3;
        private System.Windows.Forms.TabPage tabPageKModule;
        private System.Windows.Forms.TabPage tabPageCallback;
        private System.Windows.Forms.TabPage tabPageFilter;
        private System.Windows.Forms.TabPage tabPageKVar;
        private System.Windows.Forms.TabPage tabPageKThread;
        private System.Windows.Forms.TabPage tabPageKTimer;
        private System.Windows.Forms.TabPage tabPageDPC;
        private System.Windows.Forms.TabPage tabPageInterrupt;
        private System.Windows.Forms.TabPage tabPageGDT;
        private System.Windows.Forms.TabPage tabPageIDT;
        private System.Windows.Forms.TabPage tabPagePoolTag;
        private System.Windows.Forms.TabPage tabPageSSDT;
        private System.Windows.Forms.TabPage tabPageSSSDT;
        private System.Windows.Forms.TabPage tabPageObject;
        private System.Windows.Forms.TabPage tabPageHAL;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.TabPage tabPage8;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPageACPI;
        private System.Windows.Forms.TabPage tabPageAPIC;
        private System.Windows.Forms.TabPage tabPageIOAPIC;
        private System.Windows.Forms.TabPage tabPagePCI;
        private System.Windows.Forms.TabPage tabPageTimers;
        private System.Windows.Forms.TabPage tabPageSMBUS;
        private System.Windows.Forms.TabPage tabPageDIMM;
        private System.Windows.Forms.TabPage tabPageCPU;
        private System.Windows.Forms.TabPage tabPageIOPorts;
        private System.Windows.Forms.TabPage tabPageMMIO;
        private System.Windows.Forms.TabPage tabPageDMA;
        private System.Windows.Forms.TabPage tabPageDisk;
        private System.Windows.Forms.TabPage tabPageUSB;
        private System.Windows.Forms.TabPage tabPageVideo;
        private System.Windows.Forms.TabPage tabPageTPM;
        private System.Windows.Forms.TabPage tabPageNIC;
        private System.Windows.Forms.TabPage tabPageMonitor;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.TabPage tabPage10;
        private System.Windows.Forms.TabPage tabPage11;
        private System.Windows.Forms.TabPage tabPage12;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel4;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel5;
        private System.Windows.Forms.ColumnHeader EPROCESS;
    }
}

