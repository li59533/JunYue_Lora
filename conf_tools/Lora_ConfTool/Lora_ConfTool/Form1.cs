using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Lora_ConfTool
{
    public partial class Form1 : Form
    {
        public static SerialPort _serialPort;
        public static bool serial_status = false;


        public Form1()
        {
            InitializeComponent();
        }

        private void btn_serial_switch_Click(object sender, EventArgs e)
        {

            if (serial_status == false)
            {

                _serialPort = new SerialPort();

                string test_str;
                test_str = _serialPort.PortName.ToString();
                Console.Write("%s", test_str);
                _serialPort.PortName = cbx_comx.SelectedItem.ToString();
                _serialPort.BaudRate = 115200;
                _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), "None", true);
                _serialPort.DataBits = 8;
                _serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "1", true);
                //_serialPort.Handshake = ;

                // Set the read/write timeouts
                _serialPort.ReadTimeout = 500;
                _serialPort.WriteTimeout = 500;
                serial_status = true;
                btn_serial_switch.Text = "Close";
                _serialPort.Open();

                _serialPort.DataReceived += new SerialDataReceivedEventHandler(_serialPort_DataReceived);

            }
            else if (serial_status == true)
            {
                serial_status = false;
                btn_serial_switch.Text = "Open";
                _serialPort.Close();


            }

        }

        private void _serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            System.Threading.Thread.Sleep(100);
            this.Invoke((EventHandler)(delegate
            {
                Byte[] revdatabuf = new byte[_serialPort.BytesToRead];
                _serialPort.Read(revdatabuf, 0, revdatabuf.Length);
                if (revdatabuf.Length > 0)
                {
                    rev_process(revdatabuf, (UInt16)revdatabuf.Length);
                }



                for (int i = 0; i < revdatabuf.Length; i++)
                {
                    tbx_revdata.Text += revdatabuf[i].ToString("X2") + " ";
                }
                tbx_revdata.Text += "\r\n";
                _serialPort.DiscardInBuffer();
            }
                ));
        }

        UInt32 rev_count = 0;

        public void rev_process(Byte[] buf, UInt16 len)
        {
            if (buf[0] == 0x7E)
            {
                if (len == (buf[1] + buf[2] * 256))
                {
                    //byte[] newA=  a.Skip(2).Take(5).ToArray();  

                    switch (buf[5])
                    {
                        case 0x04:
                            {

                                rev_conf_resp(buf.Skip(6).Take(len - 6).ToArray(), (UInt16)(len - 6));
                            }
                            break;

                        case 0x81:
                            {
                                byte[] version = buf.Skip(6).Take(4).ToArray();
                                getversion_resp_process(version, (UInt16)version.Length);
                            }
                            break;
                        case 0xc8:
                            {
                                rev_reportData(buf.Skip(6).Take(len - 6).ToArray(), (UInt16)(len - 6));
                            }
                            break;
                        default: break;
                    }

                }

            }
        }

        public byte rev_calc_checksum(byte[] buf, UInt16 len)
        {
            byte sum = 0;
            for (uint i = 1; i < len - 3; i++)
            {
                sum += buf[i];
            }
            return sum;
        }

        public void getversion_resp_process(byte[] buf, UInt16 len)
        {
            lab_version.Text = buf[2].ToString("D") + "." + buf[1].ToString("D") + "." + buf[0].ToString("D");
        }

        private void btn_getversion_Click(object sender, EventArgs e)
        {

            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0x80; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
                cbx_comx.Items.Add(s);
            }
            cbx_comx.SelectedIndex = 0;

            if (serial_status)
            {
                btn_serial_switch.Text = "Close";

            }
            else
            {
                btn_serial_switch.Text = "Open";
            }
        }

        public void rev_conf_resp(Byte[] buf, UInt16 len)
        {
            byte[] sn = new byte[8];
            float X_k;
            float Y_k;
            float Z_k;
            float X_ADC_k;
            float Y_ADC_k;
            float Z_ADC_k;
            float battery;
            float float_temp;
            UInt32 rtc_temp;
            UInt32 sleep_time;
            UInt16 ptr_count = 0;
            Int16 len_temp;

            len_temp = (Int16)len;


            while (len_temp > 0)
            {
                len_temp = (Int16)(len - ptr_count);
                if (len_temp <= 1)
                {
                    break;
                }
                byte[] tlv = buf.Skip(ptr_count).Take(len_temp).ToArray();

                

                switch (tlv[0])
                {
                    case 1:
                        {
                            if (tlv[1] == 8)
                            {
                                sn = tlv.Skip(2).Take(8).ToArray();
                                tbx_sn.Text = (char )sn[0] + sn[1].ToString("D") + sn[4].ToString("X2") + sn[5].ToString("X2") + sn[6].ToString("X2") + sn[7].ToString("X2");
                            }
                        }
                        break;
                    case 2:
                        {
                            X_k = BitConverter.ToSingle(tlv, 2);
                            float_temp = (float )1.0 / X_k;
                            tbx_x_k.Text = float_temp.ToString();
                        }
                        break;
                    case 3:
                        {
                            Y_k = BitConverter.ToSingle(tlv, 2);
                            float_temp = (float)1.0 / Y_k;
                            tbx_y_k.Text = float_temp.ToString();

                        }
                        break;
                    case 4:
                        {
                            Z_k = BitConverter.ToSingle(tlv, 2);
                            float_temp = (float)1.0 / Z_k;
                            tbx_z_k.Text = float_temp.ToString();
                        }
                        break;
                    case 5:
                        {
                            X_ADC_k = BitConverter.ToSingle(tlv, 2);

                            tbx_x_adc_k.Text = X_ADC_k.ToString();
                        }
                        break;
                    case 6:
                        {
                            Y_ADC_k = BitConverter.ToSingle(tlv, 2);
                            tbx_y_adc_k.Text = Y_ADC_k.ToString();
                        }
                        break;
                    case 7:
                        {
                            Z_ADC_k = BitConverter.ToSingle(tlv, 2);

                            tbx_z_adc_k.Text = Z_ADC_k.ToString();
                        }
                        break;
                    case 8:
                        {
                            battery = BitConverter.ToSingle(tlv, 2);
                            tbx_battery.Text = battery.ToString();
                        }
                        break;
                    case 9:
                        {
                            rtc_temp =(UInt32) BitConverter.ToInt32(tlv,2);
                            System.DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new System.DateTime(1970, 1, 1)); // 当地时区
                            DateTime dt_temp = startTime.AddSeconds(rtc_temp);
                            tbx_rtc.Text = dt_temp.ToString();
                        }
                        break;
                    case 10:
                        {
                            sleep_time = (UInt32)BitConverter.ToInt32(tlv, 2);
                            tbx_sleeptime.Text = sleep_time.ToString("D");
                        }
                        break;
                    default:break;

                }

                ptr_count = (UInt16)(ptr_count + tlv[1] + 2);
            }
            
        }

        public void rev_reportData(Byte[] buf, UInt16 len)
        {
            float[] Acc = new float[3];
            float[] Speed = new float[3];
            float[] Displace = new float[3];
            float[] Kur = new float[3];
            float[] Env = new float[3];
            float temperature;
            float battery;

            Acc[1] = BitConverter.ToSingle(buf, 0 + 2);
            Speed[1] = BitConverter.ToSingle(buf, 4 + 2*2);
            Displace[1] = BitConverter.ToSingle(buf, 4 * 2 + 2*3 );
            Kur[1] = BitConverter.ToSingle(buf, 4 * 3 + 2 * 4);
            Env[1] = BitConverter.ToSingle(buf, 4 * 4 + 2 * 5);

            Acc[2] = BitConverter.ToSingle(buf, 4 * 5 + 2 * 6);
            Speed[2] = BitConverter.ToSingle(buf, 4 * 6 + 2 * 7);
            Displace[2] = BitConverter.ToSingle(buf, 4 * 7 + 2 * 8);
            Kur[2] = BitConverter.ToSingle(buf, 4 * 8 + 2 * 9);
            Env[2] = BitConverter.ToSingle(buf, 4 * 9 + 2 * 10);

            Acc[0] = BitConverter.ToSingle(buf, 4 * 10 + 2 * 11);
            Speed[0] = BitConverter.ToSingle(buf, 4 * 11 + 2 * 12);
            Displace[0] = BitConverter.ToSingle(buf, 4 * 12 + 2 * 13);
            Kur[0] = BitConverter.ToSingle(buf, 4 * 13 + 2 * 14);
            Env[0] = BitConverter.ToSingle(buf, 4 * 14 + 2 * 15);

            temperature = BitConverter.ToSingle(buf, 4 * 15 + 2 * 16);
            battery = BitConverter.ToSingle(buf, 4 * 16 + 2 * 17);


            ListViewItem lvi_X = new ListViewItem(rev_count.ToString());
            lvi_X.SubItems.Add(Acc[1].ToString());
            lvi_X.SubItems.Add(Speed[1].ToString());
            lvi_X.SubItems.Add(Displace[1].ToString());
            lvi_X.SubItems.Add(Kur[1].ToString());
            lvi_X.SubItems.Add(Env[1].ToString());
            lvw_X_axis.Items.Add(lvi_X);
            lvw_X_axis.Items[lvw_X_axis.Items.Count - 1].EnsureVisible();

            ListViewItem lvi_Y = new ListViewItem(rev_count.ToString());
            lvi_Y.SubItems.Add(Acc[2].ToString());
            lvi_Y.SubItems.Add(Speed[2].ToString());
            lvi_Y.SubItems.Add(Displace[2].ToString());
            lvi_Y.SubItems.Add(Kur[2].ToString());
            lvi_Y.SubItems.Add(Env[2].ToString());
            lvw_Y_axis.Items.Add(lvi_Y);
            lvw_Y_axis.Items[lvw_Y_axis.Items.Count - 1].EnsureVisible();

            ListViewItem lvi_Z = new ListViewItem(rev_count.ToString());
            lvi_Z.SubItems.Add(Acc[0].ToString());
            lvi_Z.SubItems.Add(Speed[0].ToString());
            lvi_Z.SubItems.Add(Displace[0].ToString());
            lvi_Z.SubItems.Add(Kur[0].ToString());
            lvi_Z.SubItems.Add(Env[0].ToString());
            lvw_Z_axis.Items.Add(lvi_Z);
            lvw_Z_axis.Items[lvw_Z_axis.Items.Count - 1].EnsureVisible();

            ListViewItem lvi_Other = new ListViewItem(rev_count.ToString());
            lvi_Other.SubItems.Add(temperature.ToString());
            lvi_Other.SubItems.Add(battery.ToString());
      
            lvw_Other.Items.Add(lvi_Other);
            lvw_Other.Items[lvw_Other.Items.Count - 1].EnsureVisible();





            if (rev_count >= 10)
            {
                rev_count = 0;
                lvw_X_axis.Items.Clear();
                lvw_Y_axis.Items.Clear();
                lvw_Z_axis.Items.Clear();
                lvw_Other.Items.Clear();
                tbx_revdata.Text = "";
            }

            rev_count++;
        }

        private void btn_getconf_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0x03; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);

        }

        public  enum LN_Protocol_Conf_Tag_e 
        {
            TAG_CONF_SN = 1,
            TAG_CONF_X_K = 2,
            TAG_CONF_Y_K = 3,
            TAG_CONF_Z_K = 4,
            TAG_CONF_X_ADC_K = 5,
            TAG_CONF_Y_ADC_K = 6,
            TAG_CONF_Z_ADC_K = 7,
            TAG_CONF_CUR_BATTERY = 8,
            TAG_CONF_RTC = 9,
            TAG_CONF_SLEEPTIME = 10

        };
        

        private void btn_setconfAll_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[200];
            byte[] float_temp = new byte[4];
            byte[] uint32_temp = new byte[4];
            float x_k = (float)1.0 / Convert.ToSingle(tbx_x_k.Text.ToString());
            float y_k =(float)1.0 / Convert.ToSingle(tbx_y_k.Text.ToString());
            float z_k = (float )1.0 / Convert.ToSingle(tbx_z_k.Text.ToString());
            float x_adc_k = Convert.ToSingle(tbx_x_adc_k.Text.ToString());
            float y_adc_k = Convert.ToSingle(tbx_y_adc_k.Text.ToString());
            float z_adc_k = Convert.ToSingle(tbx_z_adc_k.Text.ToString());
            float battery = Convert.ToSingle(tbx_battery.Text.ToString());


            TimeSpan ts = DateTime.Now - new DateTime(1970, 1, 1, 8, 0, 0, 0);
            UInt32 rtc_temp = Convert.ToUInt32(ts.TotalSeconds);

            UInt32 sleeptime = Convert.ToUInt32(tbx_sleeptime.Text.ToString());

            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 72;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0x01; //cmd
            // ---------TAG_CONF_SN-------------
            setconf_buf[6] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_SN;
            setconf_buf[7] = 8;
            byte [] sn_temp = Encoding.ASCII.GetBytes(tbx_sn.Text.Trim());
            setconf_buf[8] = sn_temp[0];
            setconf_buf[9] = (byte)((sn_temp[1] - '0') * 100 + (sn_temp[2] - '0') * 10 + (sn_temp[3] - '0'));
            setconf_buf[10] = 0x00;
            setconf_buf[11] = 0x00;
            setconf_buf[12] = (byte)((sn_temp[4] - '0') * 16 + (sn_temp[5] - '0'));
            setconf_buf[13] = (byte)((sn_temp[6] - '0') * 16 + (sn_temp[7] - '0'));
            setconf_buf[14] = (byte)((sn_temp[8] - '0') * 16 + (sn_temp[9] - '0'));
            setconf_buf[15] = (byte)((sn_temp[10] - '0') * 16 + (sn_temp[11] - '0'));
            // ---------TAG_CONF_X_K-------------
            setconf_buf[16] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_X_K;
            setconf_buf[17] = 4;

            float_temp = BitConverter.GetBytes(x_k);
            setconf_buf[18] = float_temp[0];
            setconf_buf[19] = float_temp[1];
            setconf_buf[20] = float_temp[2];
            setconf_buf[21] = float_temp[3];
            // --------TAG_CONF_Y_K-----------------
            setconf_buf[22] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_Y_K;
            setconf_buf[23] = 4;
            float_temp = BitConverter.GetBytes(y_k);
            setconf_buf[24] = float_temp[0];
            setconf_buf[25] = float_temp[1];
            setconf_buf[26] = float_temp[2];
            setconf_buf[27] = float_temp[3];
            // --------TAG_CONF_Z_K-----------------
            setconf_buf[28] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_Z_K;
            setconf_buf[29] = 4;
            float_temp = BitConverter.GetBytes(z_k);
            setconf_buf[30] = float_temp[0];
            setconf_buf[31] = float_temp[1];
            setconf_buf[32] = float_temp[2];
            setconf_buf[33] = float_temp[3];
            // --------TAG_CONF_X_ADC_K-----------------
            setconf_buf[34] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_X_ADC_K;
            setconf_buf[35] = 4;
            float_temp = BitConverter.GetBytes(x_adc_k);
            setconf_buf[36] = float_temp[0];
            setconf_buf[37] = float_temp[1];
            setconf_buf[38] = float_temp[2];
            setconf_buf[39] = float_temp[3];
            // --------TAG_CONF_Y_ADC_K-----------------
            setconf_buf[40] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_Y_ADC_K;
            setconf_buf[41] = 4;
            float_temp = BitConverter.GetBytes(y_adc_k);
            setconf_buf[42] = float_temp[0];
            setconf_buf[43] = float_temp[1];
            setconf_buf[44] = float_temp[2];
            setconf_buf[45] = float_temp[3];
            // --------TAG_CONF_Z_ADC_K-----------------
            setconf_buf[46] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_Z_ADC_K;
            setconf_buf[47] = 4;
            float_temp = BitConverter.GetBytes(z_adc_k);
            setconf_buf[48] = float_temp[0];
            setconf_buf[49] = float_temp[1];
            setconf_buf[50] = float_temp[2];
            setconf_buf[51] = float_temp[3];
            // --------TAG_CONF_CUR_BATTERY-----------------
            setconf_buf[52] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_CUR_BATTERY;
            setconf_buf[53] = 4;
            float_temp = BitConverter.GetBytes(battery);
            setconf_buf[54] = float_temp[0];
            setconf_buf[55] = float_temp[1];
            setconf_buf[56] = float_temp[2];
            setconf_buf[57] = float_temp[3];
            // --------TAG_CONF_RTC-----------------
            setconf_buf[58] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_RTC;
            setconf_buf[59] = 4;
            uint32_temp = BitConverter.GetBytes(rtc_temp);
            setconf_buf[60] = uint32_temp[0];
            setconf_buf[61] = uint32_temp[1];
            setconf_buf[62] = uint32_temp[2];
            setconf_buf[63] = uint32_temp[3];
            // --------TAG_CONF_SLEEPTIME-----------------
            setconf_buf[64] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_SLEEPTIME;
            setconf_buf[65] = 4;
            uint32_temp = BitConverter.GetBytes(sleeptime);
            setconf_buf[66] = uint32_temp[0];
            setconf_buf[67] = uint32_temp[1];
            setconf_buf[68] = uint32_temp[2];
            setconf_buf[69] = uint32_temp[3];

            setconf_buf[70] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 71; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[71] = check_sum;


            _serialPort.Write(setconf_buf, 0, 72);


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            DateTime dt = DateTime.Now;
            lab_localtime.Text = dt.ToString();

            TimeSpan ts = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            lab_timstamp.Text = Convert.ToInt64(ts.TotalSeconds).ToString(); 
        }

        private void btn_getsn_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0x03; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);
        }

        private void btn_setsn_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[200];

            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 18;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;

            setconf_buf[5] = 0x01; //cmd
            // ---------TAG_CONF_SN-------------
            setconf_buf[6] = (byte)LN_Protocol_Conf_Tag_e.TAG_CONF_SN;
            setconf_buf[7] = 8;
            byte[] sn_temp = Encoding.ASCII.GetBytes(tbx_sn.Text.Trim());
            setconf_buf[8] = sn_temp[0];
            setconf_buf[9] = (byte)((sn_temp[1] - '0') * 100 + (sn_temp[2] - '0') * 10 + (sn_temp[3] - '0'));
            setconf_buf[10] = 0x00;
            setconf_buf[11] = 0x00;
            setconf_buf[12] = (byte)((sn_temp[4] - '0') * 16 + (sn_temp[5] - '0'));
            setconf_buf[13] = (byte)((sn_temp[6] - '0') * 16 + (sn_temp[7] - '0'));
            setconf_buf[14] = (byte)((sn_temp[8] - '0') * 16 + (sn_temp[9] - '0'));
            setconf_buf[15] = (byte)((sn_temp[10] - '0') * 16 + (sn_temp[11] - '0'));
         
            setconf_buf[16] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 17; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[17] = check_sum;


            _serialPort.Write(setconf_buf, 0, 18);

        }

        private void btn_GetData_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0xc7; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);
        }

        private void btn_AutoReport_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0xc9; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);
        }

        private void btn_AutoData2_Click(object sender, EventArgs e)
        {
            byte[] setconf_buf = new byte[100];
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 8;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0xc9; //cmd

            setconf_buf[6] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 7; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[7] = check_sum;


            _serialPort.Write(setconf_buf, 0, 8);
        }

        private void btn_other_Click(object sender, EventArgs e)
        {

        }
    }
}
