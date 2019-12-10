using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
   
    public partial class YLJtools : Form
    {


        public static SerialPort _serialPort;
        public static bool serial_status = false;

        public YLJtools()
        {
            InitializeComponent();

        }

        private void YLJtools_Load(object sender, EventArgs e)
        {

            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
                cbx_comx.Items.Add(s);
            }
            cbx_comx.SelectedIndex = 0;
            foreach (string s in Enum.GetNames(typeof(Parity)))
            {
                Console.WriteLine("   {0}", s);
                cbx_paritybit.Items.Add(s);
            }
            cbx_paritybit.SelectedIndex = 0;
            foreach (string s in Enum.GetNames(typeof(StopBits)))
            {
                Console.WriteLine("   {0}", s);
                cbx_stopbit.Items.Add(s);
            }
            cbx_stopbit.SelectedIndex = 1;

            tbx_baud.Text = "115200";
            tbx_databit.Text = "8";

            if (serial_status)
            {
                btn_serial_switch.Text = "Close";
                
            }
            else
            {
                btn_serial_switch.Text = "Open";
            }

        }

        private void btn_serial_switch_Click(object sender, EventArgs e)
        {

            string parity;
            string stopBits;
           
           


            if (serial_status == false)
            {

                 _serialPort = new SerialPort();
                parity = cbx_paritybit.SelectedItem.ToString();
                stopBits = cbx_stopbit.SelectedItem.ToString();
                //Console.WriteLine("_serialPort.PortName : %s", _serialPort.PortName.ToString());
                string test_str;
                test_str = _serialPort.PortName.ToString();
                Console.Write("%s", test_str);
                _serialPort.PortName = cbx_comx.SelectedItem.ToString();
                _serialPort.BaudRate = Convert.ToInt32( tbx_baud.Text.ToString());
                _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), parity, true);
                _serialPort.DataBits = Convert.ToInt32(tbx_databit.Text.ToString());
                _serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), stopBits, true);
                //_serialPort.Handshake = ;

                // Set the read/write timeouts
                _serialPort.ReadTimeout = 500;
                _serialPort.WriteTimeout = 500;
                serial_status = true;
                btn_serial_switch.Text = "Close";
                _serialPort.Open();

                _serialPort.DataReceived += new SerialDataReceivedEventHandler(_serialPort_DataReceived);



            }
            else if(serial_status == true)
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

        public byte rev_calc_checksum(byte[] buf, UInt16 len)
        {
            byte sum = 0;
            for (uint i = 1; i < len - 3; i++)
            {
                sum += buf[i];
            }
            return sum;
        }


        public void rev_process(Byte[] buf,UInt16 len)
        {
            if (buf[0] == 0x7E)
            {
                if (buf[1] == 0x42)
                {
                    if (len == (buf[2] + buf[3] * 256 + 6))
                    {
                        if (rev_calc_checksum(buf, len) == buf[len - 2])
                        {
                            rev_count++;
                            float acc_peak;
                            float base_frequency;
                            float harmonic_peak_0_5;
                            float harmonic_peak_1;
                            float harmonic_peak_1_5;
                            float harmonic_peak_2;
                            float harmonic_peak_2_5;
                            float harmonic_peak_3;
                            float harmonic_peak_4;
                            float harmonic_peak_5;
                            float harmonic_peak_6;
                            float speed_peak;
                            float offset_peak;
                            float temperature;
                            byte power;
                            acc_peak = BitConverter.ToSingle(buf, 4);
                            base_frequency = BitConverter.ToSingle(buf, 4 * 2);
                            harmonic_peak_0_5 = BitConverter.ToSingle(buf, 4 * 3);
                            harmonic_peak_1 = BitConverter.ToSingle(buf, 4 * 4);
                            harmonic_peak_1_5 = BitConverter.ToSingle(buf, 4 * 5);
                            harmonic_peak_2 = BitConverter.ToSingle(buf, 4 * 6);
                            harmonic_peak_2_5 = BitConverter.ToSingle(buf, 4 * 7);
                            harmonic_peak_3 = BitConverter.ToSingle(buf, 4 * 8);
                            harmonic_peak_4 = BitConverter.ToSingle(buf, 4 * 9);
                            harmonic_peak_5 = BitConverter.ToSingle(buf, 4 * 10);
                            harmonic_peak_6 = BitConverter.ToSingle(buf, 4 * 11);
                            speed_peak = BitConverter.ToSingle(buf, 4 * 12);
                            offset_peak = BitConverter.ToSingle(buf, 4 * 13);
                            temperature = BitConverter.ToSingle(buf, 4 * 14);
                            power = buf[4 * 15];  //BitConverter.ToSingle(buf, 4*15);


                            ListViewItem lvi = new ListViewItem(rev_count.ToString());
                            lvi.SubItems.Add(acc_peak.ToString());
                            lvi.SubItems.Add(base_frequency.ToString());
                            lvi.SubItems.Add(harmonic_peak_0_5.ToString());
                            lvi.SubItems.Add(harmonic_peak_1.ToString());
                            lvi.SubItems.Add(harmonic_peak_1_5.ToString());
                            lvi.SubItems.Add(harmonic_peak_2.ToString());
                            lvi.SubItems.Add(harmonic_peak_2_5.ToString());
                            lvi.SubItems.Add(harmonic_peak_3.ToString());
                            lvi.SubItems.Add(harmonic_peak_4.ToString());
                            lvi.SubItems.Add(harmonic_peak_5.ToString());
                            lvi.SubItems.Add(harmonic_peak_6.ToString());
                            lvi.SubItems.Add(speed_peak.ToString());
                            lvi.SubItems.Add(offset_peak.ToString());
                            lvi.SubItems.Add(temperature.ToString());
                            lvi.SubItems.Add(power.ToString("D"));
                            lvw_DataValue.Items.Add(lvi);


                            lvw_DataValue.Items[lvw_DataValue.Items.Count - 1].EnsureVisible();
                        }
                    }
                }
                else
                {
                    if (len == (buf[1] + buf[2] * 256))
                    {
                        //byte[] newA=  a.Skip(2).Take(5).ToArray();  

                        switch (buf[5])
                        {
                            case 0x04:
                                {
                                    byte[] confbuf = buf.Skip(6).Take(6).ToArray();
                                    getconf_resp_process(confbuf,(UInt16) confbuf.Length);
                                }
                                break;
                            case 0x81:
                                {
                                    byte[] version = buf.Skip(6).Take(4).ToArray();
                                    getversion_resp_process(version, (UInt16)version.Length);
                                }
                                break;
                            default:break;
                        }

                    }
                }
            }
        }

        public void getconf_resp_process(byte[] buf, UInt16 len)
        {
            switch (buf[0])
            {
                case 0x44:
                    {
                        float mv_to_Acc_p;
                        mv_to_Acc_p = BitConverter.ToSingle(buf, 2);
                        tbx_mvToacc_p.Text = mv_to_Acc_p.ToString();
                    }
                    break;
                default:break;
            }
            
        }
        public void getversion_resp_process(byte[] buf, UInt16 len)
        {
            lab_version.Text = buf[2].ToString("D") + "." + buf[1].ToString("D") + "." + buf[0].ToString("D");
        }


        private void btn_clear_Click(object sender, EventArgs e)
        {
            tbx_revdata.Text = "";
            lab_version.Text = "-.-.-";
            tbx_mvToacc_p.Text = "";
            lvw_DataValue.Items.Clear();
        }

        private void btn_SetConf_Click(object sender, EventArgs e)
        {
            // head len inf cmd tlv foot sum
            /*
             * typedef struct
                {
                    uint8_t head;
                    uint16_t len;
                    uint16_t inf;
                    uint8_t cmd;
                    uint8_t *payload;
                    uint8_t foot;
                    uint8_t sum;
                }ln_protocolintance_t;
             */

            byte[] float_temp = new byte[4];
            byte[] setconf_buf = new byte[100];
            float mv_to_acc_p = 0.0f;
            setconf_buf[0] = 0x7E;

            setconf_buf[1] = 14;
            setconf_buf[2] = 0;

            setconf_buf[3] = 0;
            setconf_buf[4] = 0;


            setconf_buf[5] = 0x01;
            setconf_buf[6] = 0x44;
            setconf_buf[7] = 0x04;

            mv_to_acc_p = Convert.ToSingle(tbx_mvToacc_p.Text.ToString());
            float_temp = BitConverter.GetBytes(mv_to_acc_p);
            setconf_buf[8] = float_temp[0];
            setconf_buf[9] = float_temp[1];
            setconf_buf[10] = float_temp[2];
            setconf_buf[11] = float_temp[3];
            setconf_buf[12] = 0x7E;

            byte check_sum = 0;

            for (uint i = 0; i < 13; i++)
            {
                check_sum += setconf_buf[i];
            }
            setconf_buf[13] = check_sum;


            _serialPort.Write( setconf_buf,0,14);

        }

        private void btn_GetConf_Click(object sender, EventArgs e)
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
    }
}
