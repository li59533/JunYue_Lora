namespace Lora_ConfTool
{
    partial class Form1
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
            this.Serial_Conf = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbx_comx = new System.Windows.Forms.ComboBox();
            this.btn_serial_switch = new System.Windows.Forms.Button();
            this.tbx_revdata = new System.Windows.Forms.TextBox();
            this.Version = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.lab_version = new System.Windows.Forms.Label();
            this.btn_getversion = new System.Windows.Forms.Button();
            this.Serial_Conf.SuspendLayout();
            this.Version.SuspendLayout();
            this.SuspendLayout();
            // 
            // Serial_Conf
            // 
            this.Serial_Conf.Controls.Add(this.btn_serial_switch);
            this.Serial_Conf.Controls.Add(this.cbx_comx);
            this.Serial_Conf.Controls.Add(this.label1);
            this.Serial_Conf.Location = new System.Drawing.Point(12, 12);
            this.Serial_Conf.Name = "Serial_Conf";
            this.Serial_Conf.Size = new System.Drawing.Size(238, 88);
            this.Serial_Conf.TabIndex = 0;
            this.Serial_Conf.TabStop = false;
            this.Serial_Conf.Text = "Serial_Conf";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "COM";
            // 
            // cbx_comx
            // 
            this.cbx_comx.FormattingEnabled = true;
            this.cbx_comx.Location = new System.Drawing.Point(36, 13);
            this.cbx_comx.Name = "cbx_comx";
            this.cbx_comx.Size = new System.Drawing.Size(52, 20);
            this.cbx_comx.TabIndex = 1;
            // 
            // btn_serial_switch
            // 
            this.btn_serial_switch.Location = new System.Drawing.Point(94, 13);
            this.btn_serial_switch.Name = "btn_serial_switch";
            this.btn_serial_switch.Size = new System.Drawing.Size(75, 23);
            this.btn_serial_switch.TabIndex = 2;
            this.btn_serial_switch.Text = "Open";
            this.btn_serial_switch.UseVisualStyleBackColor = true;
            this.btn_serial_switch.Click += new System.EventHandler(this.btn_serial_switch_Click);
            // 
            // tbx_revdata
            // 
            this.tbx_revdata.Location = new System.Drawing.Point(21, 390);
            this.tbx_revdata.Multiline = true;
            this.tbx_revdata.Name = "tbx_revdata";
            this.tbx_revdata.Size = new System.Drawing.Size(680, 48);
            this.tbx_revdata.TabIndex = 1;
            // 
            // Version
            // 
            this.Version.Controls.Add(this.btn_getversion);
            this.Version.Controls.Add(this.lab_version);
            this.Version.Controls.Add(this.label2);
            this.Version.Location = new System.Drawing.Point(652, 12);
            this.Version.Name = "Version";
            this.Version.Size = new System.Drawing.Size(120, 50);
            this.Version.TabIndex = 2;
            this.Version.TabStop = false;
            this.Version.Text = "Version";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(11, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "V";
            // 
            // lab_version
            // 
            this.lab_version.AutoSize = true;
            this.lab_version.Location = new System.Drawing.Point(24, 20);
            this.lab_version.Name = "lab_version";
            this.lab_version.Size = new System.Drawing.Size(35, 12);
            this.lab_version.TabIndex = 1;
            this.lab_version.Text = "_._._";
            // 
            // btn_getversion
            // 
            this.btn_getversion.Location = new System.Drawing.Point(65, 18);
            this.btn_getversion.Name = "btn_getversion";
            this.btn_getversion.Size = new System.Drawing.Size(49, 23);
            this.btn_getversion.TabIndex = 2;
            this.btn_getversion.Text = "--";
            this.btn_getversion.UseVisualStyleBackColor = true;
            this.btn_getversion.Click += new System.EventHandler(this.btn_getversion_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Version);
            this.Controls.Add(this.tbx_revdata);
            this.Controls.Add(this.Serial_Conf);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Serial_Conf.ResumeLayout(false);
            this.Serial_Conf.PerformLayout();
            this.Version.ResumeLayout(false);
            this.Version.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox Serial_Conf;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_serial_switch;
        private System.Windows.Forms.ComboBox cbx_comx;
        private System.Windows.Forms.TextBox tbx_revdata;
        private System.Windows.Forms.GroupBox Version;
        private System.Windows.Forms.Button btn_getversion;
        private System.Windows.Forms.Label lab_version;
        private System.Windows.Forms.Label label2;
    }
}

