namespace WindowsFormsApp1
{
    partial class YLJtools
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
            this.btn_serial_switch = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.Serial_Conf = new System.Windows.Forms.GroupBox();
            this.cbx_stopbit = new System.Windows.Forms.ComboBox();
            this.cbx_paritybit = new System.Windows.Forms.ComboBox();
            this.tbx_databit = new System.Windows.Forms.TextBox();
            this.tbx_baud = new System.Windows.Forms.TextBox();
            this.cbx_comx = new System.Windows.Forms.ComboBox();
            this.tbx_revdata = new System.Windows.Forms.TextBox();
            this.lvw_DataValue = new System.Windows.Forms.ListView();
            this.xuhao = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.Acc_peak = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.base_freq = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak0_5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak1_5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak2_5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.har_peak6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.speed_RMS = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.dis_peak = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.temperature = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.power = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btn_clear = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_SetConf = new System.Windows.Forms.Button();
            this.btn_GetConf = new System.Windows.Forms.Button();
            this.tbx_mvToacc_p = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btn_getversion = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.lab_version = new System.Windows.Forms.Label();
            this.Serial_Conf.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_serial_switch
            // 
            this.btn_serial_switch.Location = new System.Drawing.Point(584, 20);
            this.btn_serial_switch.Name = "btn_serial_switch";
            this.btn_serial_switch.Size = new System.Drawing.Size(75, 23);
            this.btn_serial_switch.TabIndex = 0;
            this.btn_serial_switch.Text = "打开";
            this.btn_serial_switch.UseVisualStyleBackColor = true;
            this.btn_serial_switch.Click += new System.EventHandler(this.btn_serial_switch_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "COM：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(461, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "校验位";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(363, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "停止位：";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(265, 25);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 5;
            this.label5.Text = "数据位：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(134, 25);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 6;
            this.label6.Text = "波特率：";
            // 
            // Serial_Conf
            // 
            this.Serial_Conf.Controls.Add(this.cbx_stopbit);
            this.Serial_Conf.Controls.Add(this.cbx_paritybit);
            this.Serial_Conf.Controls.Add(this.tbx_databit);
            this.Serial_Conf.Controls.Add(this.tbx_baud);
            this.Serial_Conf.Controls.Add(this.cbx_comx);
            this.Serial_Conf.Controls.Add(this.label3);
            this.Serial_Conf.Controls.Add(this.btn_serial_switch);
            this.Serial_Conf.Controls.Add(this.label6);
            this.Serial_Conf.Controls.Add(this.label1);
            this.Serial_Conf.Controls.Add(this.label5);
            this.Serial_Conf.Controls.Add(this.label4);
            this.Serial_Conf.Location = new System.Drawing.Point(12, 12);
            this.Serial_Conf.Name = "Serial_Conf";
            this.Serial_Conf.Size = new System.Drawing.Size(667, 61);
            this.Serial_Conf.TabIndex = 7;
            this.Serial_Conf.TabStop = false;
            this.Serial_Conf.Text = "Serial_Conf";
            // 
            // cbx_stopbit
            // 
            this.cbx_stopbit.FormattingEnabled = true;
            this.cbx_stopbit.Location = new System.Drawing.Point(409, 21);
            this.cbx_stopbit.Name = "cbx_stopbit";
            this.cbx_stopbit.Size = new System.Drawing.Size(46, 20);
            this.cbx_stopbit.TabIndex = 12;
            // 
            // cbx_paritybit
            // 
            this.cbx_paritybit.FormattingEnabled = true;
            this.cbx_paritybit.Location = new System.Drawing.Point(508, 21);
            this.cbx_paritybit.Name = "cbx_paritybit";
            this.cbx_paritybit.Size = new System.Drawing.Size(59, 20);
            this.cbx_paritybit.TabIndex = 11;
            // 
            // tbx_databit
            // 
            this.tbx_databit.Location = new System.Drawing.Point(320, 21);
            this.tbx_databit.Name = "tbx_databit";
            this.tbx_databit.Size = new System.Drawing.Size(37, 21);
            this.tbx_databit.TabIndex = 9;
            // 
            // tbx_baud
            // 
            this.tbx_baud.Location = new System.Drawing.Point(193, 21);
            this.tbx_baud.Name = "tbx_baud";
            this.tbx_baud.Size = new System.Drawing.Size(65, 21);
            this.tbx_baud.TabIndex = 8;
            // 
            // cbx_comx
            // 
            this.cbx_comx.FormattingEnabled = true;
            this.cbx_comx.Location = new System.Drawing.Point(53, 21);
            this.cbx_comx.Name = "cbx_comx";
            this.cbx_comx.Size = new System.Drawing.Size(75, 20);
            this.cbx_comx.TabIndex = 7;
            // 
            // tbx_revdata
            // 
            this.tbx_revdata.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tbx_revdata.Location = new System.Drawing.Point(6, 20);
            this.tbx_revdata.Multiline = true;
            this.tbx_revdata.Name = "tbx_revdata";
            this.tbx_revdata.Size = new System.Drawing.Size(963, 106);
            this.tbx_revdata.TabIndex = 8;
            // 
            // lvw_DataValue
            // 
            this.lvw_DataValue.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lvw_DataValue.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.xuhao,
            this.Acc_peak,
            this.base_freq,
            this.har_peak0_5,
            this.har_peak1,
            this.har_peak1_5,
            this.har_peak2,
            this.har_peak2_5,
            this.har_peak3,
            this.har_peak4,
            this.har_peak5,
            this.har_peak6,
            this.speed_RMS,
            this.dis_peak,
            this.temperature,
            this.power});
            this.lvw_DataValue.GridLines = true;
            this.lvw_DataValue.HideSelection = false;
            this.lvw_DataValue.Location = new System.Drawing.Point(6, 137);
            this.lvw_DataValue.Name = "lvw_DataValue";
            this.lvw_DataValue.Size = new System.Drawing.Size(1097, 425);
            this.lvw_DataValue.TabIndex = 9;
            this.lvw_DataValue.UseCompatibleStateImageBehavior = false;
            this.lvw_DataValue.View = System.Windows.Forms.View.Details;
            // 
            // xuhao
            // 
            this.xuhao.Text = "序号";
            this.xuhao.Width = 38;
            // 
            // Acc_peak
            // 
            this.Acc_peak.Text = "Acc_peak";
            // 
            // base_freq
            // 
            this.base_freq.Text = "base_freq";
            this.base_freq.Width = 74;
            // 
            // har_peak0_5
            // 
            this.har_peak0_5.Text = "har_peak0.5";
            this.har_peak0_5.Width = 92;
            // 
            // har_peak1
            // 
            this.har_peak1.Text = "har_peak1";
            // 
            // har_peak1_5
            // 
            this.har_peak1_5.Text = "har_peak1.5";
            // 
            // har_peak2
            // 
            this.har_peak2.Text = "har_peak2";
            // 
            // har_peak2_5
            // 
            this.har_peak2_5.Text = "har_peak2.5";
            // 
            // har_peak3
            // 
            this.har_peak3.Text = "har_peak3";
            // 
            // har_peak4
            // 
            this.har_peak4.Text = "har_peak4";
            // 
            // har_peak5
            // 
            this.har_peak5.Text = "har_peak5";
            // 
            // har_peak6
            // 
            this.har_peak6.Text = "har_peak6";
            // 
            // speed_RMS
            // 
            this.speed_RMS.Text = "speed_RMS";
            // 
            // dis_peak
            // 
            this.dis_peak.Text = "dis_peak";
            // 
            // temperature
            // 
            this.temperature.Text = "temperature";
            // 
            // power
            // 
            this.power.Text = "power";
            // 
            // btn_clear
            // 
            this.btn_clear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_clear.Location = new System.Drawing.Point(975, 20);
            this.btn_clear.Name = "btn_clear";
            this.btn_clear.Size = new System.Drawing.Size(128, 106);
            this.btn_clear.TabIndex = 10;
            this.btn_clear.Text = "Clear";
            this.btn_clear.UseVisualStyleBackColor = true;
            this.btn_clear.Click += new System.EventHandler(this.btn_clear_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.btn_SetConf);
            this.groupBox1.Controls.Add(this.btn_GetConf);
            this.groupBox1.Controls.Add(this.tbx_mvToacc_p);
            this.groupBox1.Location = new System.Drawing.Point(685, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(334, 60);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Conf";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(142, 28);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "mv/g";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "mvToacc_P:";
            // 
            // btn_SetConf
            // 
            this.btn_SetConf.Location = new System.Drawing.Point(249, 18);
            this.btn_SetConf.Name = "btn_SetConf";
            this.btn_SetConf.Size = new System.Drawing.Size(60, 30);
            this.btn_SetConf.TabIndex = 2;
            this.btn_SetConf.Text = "SetConf";
            this.btn_SetConf.UseVisualStyleBackColor = true;
            this.btn_SetConf.Click += new System.EventHandler(this.btn_SetConf_Click);
            // 
            // btn_GetConf
            // 
            this.btn_GetConf.Location = new System.Drawing.Point(182, 18);
            this.btn_GetConf.Name = "btn_GetConf";
            this.btn_GetConf.Size = new System.Drawing.Size(60, 30);
            this.btn_GetConf.TabIndex = 1;
            this.btn_GetConf.Text = "GetConf";
            this.btn_GetConf.UseVisualStyleBackColor = true;
            this.btn_GetConf.Click += new System.EventHandler(this.btn_GetConf_Click);
            // 
            // tbx_mvToacc_p
            // 
            this.tbx_mvToacc_p.Location = new System.Drawing.Point(76, 24);
            this.tbx_mvToacc_p.Name = "tbx_mvToacc_p";
            this.tbx_mvToacc_p.Size = new System.Drawing.Size(60, 21);
            this.tbx_mvToacc_p.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.tbx_revdata);
            this.groupBox2.Controls.Add(this.lvw_DataValue);
            this.groupBox2.Controls.Add(this.btn_clear);
            this.groupBox2.Location = new System.Drawing.Point(12, 79);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1109, 568);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "data_show";
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.btn_getversion);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.lab_version);
            this.groupBox3.Location = new System.Drawing.Point(1025, 13);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(96, 60);
            this.groupBox3.TabIndex = 13;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Version";
            // 
            // btn_getversion
            // 
            this.btn_getversion.Location = new System.Drawing.Point(21, 35);
            this.btn_getversion.Name = "btn_getversion";
            this.btn_getversion.Size = new System.Drawing.Size(56, 17);
            this.btn_getversion.TabIndex = 2;
            this.btn_getversion.Text = "--";
            this.btn_getversion.UseVisualStyleBackColor = true;
            this.btn_getversion.Click += new System.EventHandler(this.btn_getversion_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(24, 19);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(11, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "V";
            // 
            // lab_version
            // 
            this.lab_version.AutoSize = true;
            this.lab_version.Location = new System.Drawing.Point(35, 18);
            this.lab_version.Name = "lab_version";
            this.lab_version.Size = new System.Drawing.Size(35, 12);
            this.lab_version.TabIndex = 0;
            this.lab_version.Text = "_._._";
            // 
            // YLJtools
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1133, 659);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Serial_Conf);
            this.Name = "YLJtools";
            this.Text = "YLJ_Tools";
            this.Load += new System.EventHandler(this.YLJtools_Load);
            this.Serial_Conf.ResumeLayout(false);
            this.Serial_Conf.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_serial_switch;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox Serial_Conf;
        private System.Windows.Forms.ComboBox cbx_paritybit;
        private System.Windows.Forms.TextBox tbx_databit;
        private System.Windows.Forms.TextBox tbx_baud;
        private System.Windows.Forms.ComboBox cbx_comx;
        private System.Windows.Forms.ComboBox cbx_stopbit;
        private System.Windows.Forms.TextBox tbx_revdata;
        private System.Windows.Forms.ListView lvw_DataValue;
        private System.Windows.Forms.ColumnHeader xuhao;
        private System.Windows.Forms.ColumnHeader Acc_peak;
        private System.Windows.Forms.ColumnHeader base_freq;
        private System.Windows.Forms.ColumnHeader har_peak0_5;
        private System.Windows.Forms.ColumnHeader har_peak1;
        private System.Windows.Forms.ColumnHeader har_peak1_5;
        private System.Windows.Forms.ColumnHeader har_peak2;
        private System.Windows.Forms.ColumnHeader har_peak2_5;
        private System.Windows.Forms.ColumnHeader har_peak3;
        private System.Windows.Forms.ColumnHeader har_peak4;
        private System.Windows.Forms.ColumnHeader har_peak5;
        private System.Windows.Forms.ColumnHeader har_peak6;
        private System.Windows.Forms.ColumnHeader speed_RMS;
        private System.Windows.Forms.ColumnHeader dis_peak;
        private System.Windows.Forms.ColumnHeader temperature;
        private System.Windows.Forms.ColumnHeader power;
        private System.Windows.Forms.Button btn_clear;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_SetConf;
        private System.Windows.Forms.Button btn_GetConf;
        private System.Windows.Forms.TextBox tbx_mvToacc_p;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btn_getversion;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lab_version;
        private System.Windows.Forms.Label label8;
    }
}

