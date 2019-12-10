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
                if (buf[1] == 0x42)
                {
                    if (len == (buf[2] + buf[3] * 256 + 6))
                    {
                        if (rev_calc_checksum(buf, len) == buf[len - 2])
                        {
                            rev_count++;
                            
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
                                  
                                }
                                break;
                            case 0x81:
                                {
                                    byte[] version = buf.Skip(6).Take(4).ToArray();
                                    getversion_resp_process(version, (UInt16)version.Length);
                                }
                                break;
                            default: break;
                        }

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
    }
}
