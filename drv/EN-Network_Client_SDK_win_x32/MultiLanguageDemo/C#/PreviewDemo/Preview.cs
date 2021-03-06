using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Text;

using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace PreviewDemo
{
    /// <summary>
    /// Form1 的摘要说明。
    /// </summary>
    public class Preview : System.Windows.Forms.Form
    {
        private CHCNetSDK.REALDATACALLBACK m_fRealData = null;
        private PlayCtrl.DISPLAYCBFUN m_fDisplayFun = null;
        private CHCNetSDK.MSGCallBack m_falarmData = null;
        public CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo;
        public Int32 m_lUserID = -1;
        private bool m_bInitSDK = false;
        private Int32 m_lRealHandle = -1;
        private Int32 m_lPort = -1;
        private bool m_bJpegCapture = false;
        private Int32 m_iPreviewType = 0;
        private bool m_bGuard = false;
        private bool m_bOpenSound = false;
        private Int32 m_lFortifyHandle = -1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnLogin;
        private System.Windows.Forms.Button btnPreview;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.TextBox textBoxUserName;
        private System.Windows.Forms.PictureBox RealPlayWnd;
        private Button btnJpegCapture;
        private Button btnPreviewType;
        private IntPtr m_ptrRealHandle;
        private Button btnFortify;
        private RichTextBox TextBoxInfo;
        private Label label5;
        private Button button1;
        private Button btnVoiceTalk;
        private Button btnAlarmConfig;
        private Button btnOpenSound;
        private Button btnPtzCtrl;
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.Container components = null;

        public Preview()
        {
            //
            // Windows 窗体设计器支持所必需的
            //
            InitializeComponent();

            m_bInitSDK = CHCNetSDK.NET_DVR_Init();
            if (m_bInitSDK == false)
            {
                MessageBox.Show("NET_DVR_Init error!");
                return;
            }
            else
            {
            }
            //
            // TODO: 在 InitializeComponent 调用后添加任何构造函数代码
            //
        }

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (m_lRealHandle >= 0)
            {
                CHCNetSDK.NET_DVR_StopRealPlay(m_lRealHandle);
            }
            if (m_lUserID >= 0)
            {
                CHCNetSDK.NET_DVR_Logout_V30(m_lUserID);
            }
            if (m_bInitSDK == true)
            {
                CHCNetSDK.NET_DVR_Cleanup();
            }
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码
        /// <summary>
        /// 设计器支持所需的方法 - 不要使用代码编辑器修改
        /// 此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btnLogin = new System.Windows.Forms.Button();
            this.btnPreview = new System.Windows.Forms.Button();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.textBoxUserName = new System.Windows.Forms.TextBox();
            this.RealPlayWnd = new System.Windows.Forms.PictureBox();
            this.btnJpegCapture = new System.Windows.Forms.Button();
            this.btnPreviewType = new System.Windows.Forms.Button();
            this.btnFortify = new System.Windows.Forms.Button();
            this.TextBoxInfo = new System.Windows.Forms.RichTextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.btnVoiceTalk = new System.Windows.Forms.Button();
            this.btnAlarmConfig = new System.Windows.Forms.Button();
            this.btnOpenSound = new System.Windows.Forms.Button();
            this.btnPtzCtrl = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.RealPlayWnd)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(16, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(48, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Dev IP";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(324, 13);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 16);
            this.label2.TabIndex = 0;
            this.label2.Text = "User";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(474, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 16);
            this.label3.TabIndex = 0;
            this.label3.Text = "Pass";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(166, 13);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 16);
            this.label4.TabIndex = 0;
            this.label4.Text = "Dev Port";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(629, 13);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(56, 24);
            this.btnLogin.TabIndex = 1;
            this.btnLogin.Text = "Login";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // btnPreview
            // 
            this.btnPreview.Location = new System.Drawing.Point(13, 402);
            this.btnPreview.Name = "btnPreview";
            this.btnPreview.Size = new System.Drawing.Size(56, 20);
            this.btnPreview.TabIndex = 2;
            this.btnPreview.Text = "Preview";
            this.btnPreview.Click += new System.EventHandler(this.btnPreview_Click);
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(229, 13);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(88, 21);
            this.textBoxPort.TabIndex = 3;
            this.textBoxPort.Text = "8000";
            this.textBoxPort.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(71, 13);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(88, 21);
            this.textBoxIP.TabIndex = 3;
            this.textBoxIP.Text = "172.4.46.99";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Location = new System.Drawing.Point(529, 13);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.Size = new System.Drawing.Size(88, 21);
            this.textBoxPassword.TabIndex = 3;
            this.textBoxPassword.Text = "12345";
            this.textBoxPassword.UseSystemPasswordChar = true;
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(379, 13);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(88, 21);
            this.textBoxUserName.TabIndex = 3;
            this.textBoxUserName.Text = "admin";
            // 
            // RealPlayWnd
            // 
            this.RealPlayWnd.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.RealPlayWnd.Location = new System.Drawing.Point(12, 46);
            this.RealPlayWnd.Name = "RealPlayWnd";
            this.RealPlayWnd.Size = new System.Drawing.Size(432, 328);
            this.RealPlayWnd.TabIndex = 4;
            this.RealPlayWnd.TabStop = false;
            this.RealPlayWnd.Click += new System.EventHandler(this.RealPlayWnd_Click);
            // 
            // btnJpegCapture
            // 
            this.btnJpegCapture.Location = new System.Drawing.Point(171, 402);
            this.btnJpegCapture.Name = "btnJpegCapture";
            this.btnJpegCapture.Size = new System.Drawing.Size(108, 20);
            this.btnJpegCapture.TabIndex = 5;
            this.btnJpegCapture.Text = "Jpeg Capture";
            this.btnJpegCapture.UseVisualStyleBackColor = true;
            this.btnJpegCapture.Click += new System.EventHandler(this.btnJpegCapture_Click);
            // 
            // btnPreviewType
            // 
            this.btnPreviewType.Location = new System.Drawing.Point(75, 402);
            this.btnPreviewType.Name = "btnPreviewType";
            this.btnPreviewType.Size = new System.Drawing.Size(93, 20);
            this.btnPreviewType.TabIndex = 6;
            this.btnPreviewType.Text = "CallBack Dec";
            this.btnPreviewType.UseVisualStyleBackColor = true;
            this.btnPreviewType.Click += new System.EventHandler(this.btnPreviewType_Click);
            // 
            // btnFortify
            // 
            this.btnFortify.Location = new System.Drawing.Point(282, 402);
            this.btnFortify.Name = "btnFortify";
            this.btnFortify.Size = new System.Drawing.Size(83, 20);
            this.btnFortify.TabIndex = 7;
            this.btnFortify.Text = "Guard";
            this.btnFortify.UseVisualStyleBackColor = true;
            this.btnFortify.Click += new System.EventHandler(this.btnFortify_Click);
            // 
            // TextBoxInfo
            // 
            this.TextBoxInfo.Location = new System.Drawing.Point(450, 102);
            this.TextBoxInfo.Name = "TextBoxInfo";
            this.TextBoxInfo.Size = new System.Drawing.Size(235, 256);
            this.TextBoxInfo.TabIndex = 8;
            this.TextBoxInfo.Text = "";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(461, 79);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "Debug Info";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(371, 402);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(104, 20);
            this.button1.TabIndex = 10;
            this.button1.Text = "Motion Config";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnVoiceTalk
            // 
            this.btnVoiceTalk.Location = new System.Drawing.Point(481, 401);
            this.btnVoiceTalk.Name = "btnVoiceTalk";
            this.btnVoiceTalk.Size = new System.Drawing.Size(75, 23);
            this.btnVoiceTalk.TabIndex = 11;
            this.btnVoiceTalk.Text = "voice talk";
            this.btnVoiceTalk.UseVisualStyleBackColor = true;
            this.btnVoiceTalk.Click += new System.EventHandler(this.btnVoiceTalk_Click);
            // 
            // btnAlarmConfig
            // 
            this.btnAlarmConfig.Location = new System.Drawing.Point(562, 401);
            this.btnAlarmConfig.Name = "btnAlarmConfig";
            this.btnAlarmConfig.Size = new System.Drawing.Size(96, 23);
            this.btnAlarmConfig.TabIndex = 12;
            this.btnAlarmConfig.Text = "Alram config";
            this.btnAlarmConfig.UseVisualStyleBackColor = true;
            this.btnAlarmConfig.Click += new System.EventHandler(this.btnAlarmConfig_Click);
            // 
            // btnOpenSound
            // 
            this.btnOpenSound.Location = new System.Drawing.Point(12, 429);
            this.btnOpenSound.Name = "btnOpenSound";
            this.btnOpenSound.Size = new System.Drawing.Size(75, 23);
            this.btnOpenSound.TabIndex = 13;
            this.btnOpenSound.Text = "OpenSound";
            this.btnOpenSound.UseVisualStyleBackColor = true;
            this.btnOpenSound.Click += new System.EventHandler(this.btnOpenSound_Click);
            // 
            // btnPtzCtrl
            // 
            this.btnPtzCtrl.Location = new System.Drawing.Point(106, 429);
            this.btnPtzCtrl.Name = "btnPtzCtrl";
            this.btnPtzCtrl.Size = new System.Drawing.Size(75, 23);
            this.btnPtzCtrl.TabIndex = 14;
            this.btnPtzCtrl.Text = "PTZ";
            this.btnPtzCtrl.UseVisualStyleBackColor = true;
            this.btnPtzCtrl.Click += new System.EventHandler(this.btnPtzCtrl_Click);
            // 
            // Preview
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(6, 14);
            this.ClientSize = new System.Drawing.Size(705, 466);
            this.Controls.Add(this.btnPtzCtrl);
            this.Controls.Add(this.btnOpenSound);
            this.Controls.Add(this.btnAlarmConfig);
            this.Controls.Add(this.btnVoiceTalk);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.TextBoxInfo);
            this.Controls.Add(this.btnFortify);
            this.Controls.Add(this.btnPreviewType);
            this.Controls.Add(this.btnJpegCapture);
            this.Controls.Add(this.RealPlayWnd);
            this.Controls.Add(this.textBoxPort);
            this.Controls.Add(this.btnPreview);
            this.Controls.Add(this.btnLogin);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxUserName);
            this.Name = "Preview";
            this.Text = "ClientDemo";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.RealPlayWnd)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion

        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new Preview());
        }

        private void textBox1_TextChanged(object sender, System.EventArgs e)
        {

        }

        private void btnLogin_Click(object sender, System.EventArgs e)
        {
            if (textBoxIP.Text == "" || textBoxPort.Text == "" ||
                textBoxUserName.Text == "" || textBoxPassword.Text == "")
            {
                MessageBox.Show("请输入参数");
                return;
            }
            string DVRIPAddress = textBoxIP.Text;
            Int16 DVRPortNumber = Int16.Parse(textBoxPort.Text);
            string DVRUserName = textBoxUserName.Text;
            string DVRPassword = textBoxPassword.Text;
            m_lUserID = CHCNetSDK.NET_DVR_Login_V30(DVRIPAddress, DVRPortNumber, DVRUserName, DVRPassword, ref m_struDeviceInfo);
            if (m_lUserID == -1)
            {
                MessageBox.Show("login error!");
                return;
            }
            else
            {
                MessageBox.Show("Login Success!");
            }

        }

        private void btnPreview_Click(object sender, System.EventArgs e)
        {
            CHCNetSDK.NET_DVR_CLIENTINFO lpClientInfo = new CHCNetSDK.NET_DVR_CLIENTINFO();

            lpClientInfo.lChannel = 1;
            lpClientInfo.lLinkMode = 0x0000;
            lpClientInfo.sMultiCastIP = "";
            if (m_iPreviewType == 0) // use by callback
            {
                lpClientInfo.hPlayWnd = IntPtr.Zero;// todo!!! 这边应该做2中情况考虑去编写代码
                m_ptrRealHandle = RealPlayWnd.Handle;
                m_fRealData = new CHCNetSDK.REALDATACALLBACK(RealDataCallBack);
                IntPtr pUser = new IntPtr();
                m_lRealHandle = CHCNetSDK.NET_DVR_RealPlay_V30(m_lUserID, ref lpClientInfo, m_fRealData, pUser, 1);

            }
            else if (1 == m_iPreviewType)
            {
                lpClientInfo.hPlayWnd = RealPlayWnd.Handle;
                IntPtr pUser = new IntPtr();
                m_lRealHandle = CHCNetSDK.NET_DVR_RealPlay_V30(m_lUserID, ref lpClientInfo, null, pUser, 1);
            }
            if (m_lRealHandle == -1)
            {
                uint nError = CHCNetSDK.NET_DVR_GetLastError();
                DebugInfo("NET_DVR_RealPlay fail %d!");
                return;
            }
        }

        public void RemoteDisplayCBFun(int nPort, IntPtr pBuf, int nSize, int nWidth, int nHeight, int nStamp, int nType, int nReserved)
        {
            MyDebugInfo AlarmInfo = new MyDebugInfo(DebugInfo);
            if (!m_bJpegCapture)
            {
                return;
            }
            else
            {
                uint nLastErr = 100;
                // save picture as you want
                if (!PlayCtrl.PlayM4_ConvertToJpegFile(pBuf, nSize, nWidth, nHeight, nType, "C:/Capture.jpg"))
                {
                    //Debug.WriteLine("PlayM4_ConvertToJpegFile fail");
                    nLastErr = PlayCtrl.PlayM4_GetLastError(m_lPort);
                    this.BeginInvoke(AlarmInfo, "Jpeg Capture fail");
                }
                else
                {
                    this.BeginInvoke(AlarmInfo, "Jpeg Capture Succ");
                    //Debug.WriteLine("PlayM4_ConvertToJpegFile Succ");
                }

            }
            
            m_bJpegCapture = false;
        }

        public void RealDataCallBack(Int32 lRealHandle, UInt32 dwDataType, ref byte pBuffer, UInt32 dwBufSize, IntPtr pUser)
        {
            MyDebugInfo AlarmInfo = new MyDebugInfo(DebugInfo);
            switch (dwDataType)
            {
                case CHCNetSDK.NET_DVR_SYSHEAD:     // sys head
                    if (!PlayCtrl.PlayM4_GetPort(ref m_lPort))
                    {
                        MessageBox.Show("Get Port Fail");
                    }

                    if (dwBufSize > 0)
                    {
                        //set as stream mode, real-time stream under preview
                        if (!PlayCtrl.PlayM4_SetStreamOpenMode(m_lPort, PlayCtrl.STREAME_REALTIME))
                        {
                            this.BeginInvoke(AlarmInfo, "PlayM4_SetStreamOpenMode fail");
                        }
                        //start player
                        if (!PlayCtrl.PlayM4_OpenStream(m_lPort, ref pBuffer, dwBufSize, 1024 * 1024))
                        {
                            m_lPort = -1;
                            this.BeginInvoke(AlarmInfo, "PlayM4_OpenStream fail");
                            break;
                        }
                        //set soft decode display callback function to capture
                        m_fDisplayFun = new PlayCtrl.DISPLAYCBFUN(RemoteDisplayCBFun);
                        if (!PlayCtrl.PlayM4_SetDisplayCallBack(m_lPort, m_fDisplayFun))
                        {
                            this.BeginInvoke(AlarmInfo, "PlayM4_SetDisplayCallBack fail");
                        }

                        //start play, set play window
                        this.BeginInvoke(AlarmInfo, "About to call PlayM4_Play");

                        if (!PlayCtrl.PlayM4_Play(m_lPort, m_ptrRealHandle))
                        {
                            m_lPort = -1;
                            this.BeginInvoke(AlarmInfo, "PlayM4_Play fail");
                            break;
                        }

                        //set frame buffer number

                        if (!PlayCtrl.PlayM4_SetDisplayBuf(m_lPort, 15))
                        {
                            this.BeginInvoke(AlarmInfo, "PlayM4_SetDisplayBuf fail");
                        }

                        //set display mode
                        if (!PlayCtrl.PlayM4_SetOverlayMode(m_lPort, 0, 0/* COLORREF(0)*/))//play off screen // todo!!!
                        {
                            this.BeginInvoke(AlarmInfo, " PlayM4_SetOverlayMode fail");
                        }
                    }

                    break;
                case CHCNetSDK.NET_DVR_STREAMDATA:     // video stream data
                    if (dwBufSize > 0 && m_lPort != -1)
                    {
                        if (!PlayCtrl.PlayM4_InputData(m_lPort, ref pBuffer, dwBufSize))
                        {
                            this.BeginInvoke(AlarmInfo, " PlayM4_InputData fail");
                        }
                    }
                    break;

                case CHCNetSDK.NET_DVR_AUDIOSTREAMDATA:     //  Audio Stream Data
                    if (dwBufSize > 0 && m_lPort != -1)
                    {
                        if (!PlayCtrl.PlayM4_InputVideoData(m_lPort, ref pBuffer, dwBufSize))
                        {
                            this.BeginInvoke(AlarmInfo, "PlayM4_InputVideoData Fail");
                        }
                    }

                    break;
                default:
                    break;
            }

        }



        public void MsgCallback(int lCommand, ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            MyDebugInfo AlarmInfo = new MyDebugInfo(DebugInfo);
            switch (lCommand)
            {
                case CHCNetSDK.COMM_ALARM:
                    ProcessCommAlarm(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ALARM_V30:
                    ProcessCommAlarm_V30(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ALARM_RULE:
                    this.BeginInvoke(AlarmInfo, "COMM_ALARM_RULE");
                    break;
                case CHCNetSDK.COMM_TRADEINFO:
                    this.BeginInvoke(AlarmInfo, "COMM_TRADEINFO");
                    break;
                case CHCNetSDK.COMM_IPCCFG:
                    this.BeginInvoke(AlarmInfo, "COMM_IPCCFG");
                    break;
                case CHCNetSDK.COMM_IPCCFG_V31:
                    this.BeginInvoke(AlarmInfo, "COMM_IPCCFG_V31");
                    break;
                default:
                    break;
            }
        }

        public void ProcessCommAlarm(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            MyDebugInfo AlarmInfo = new MyDebugInfo(DebugInfo);
            CHCNetSDK.NET_DVR_ALARMINFO struAlarmInfo = new CHCNetSDK.NET_DVR_ALARMINFO();

            struAlarmInfo = (CHCNetSDK.NET_DVR_ALARMINFO)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_ALARMINFO));

            string str;
            switch (struAlarmInfo.dwAlarmType)
            {
                case 0: 
                    this.BeginInvoke(AlarmInfo, "sensor alarm");
                    break;
                case 1:
                    this.BeginInvoke(AlarmInfo, "hard disk full");
                    break;
                case 2:
                    this.BeginInvoke(AlarmInfo, "video lost");
                    break;
                case 3:
                    str = "";
                    str += pAlarmer.sDeviceIP;
                    str += " motion detection";
                    this.BeginInvoke(AlarmInfo, str);
                    m_bJpegCapture = true;
                    break;
                case 4:
                    this.BeginInvoke(AlarmInfo, "hard disk unformatted");
                    break;
                case 5:
                    this.BeginInvoke(AlarmInfo, "hard disk error");
                    break;
                case 6:
                    this.BeginInvoke(AlarmInfo, "tampering detection");
                    break;
                case 7:
                    this.BeginInvoke(AlarmInfo, "unmatched video output standard");
                    break;
                case 8:
                    this.BeginInvoke(AlarmInfo, "illegal operation");
                    break;
                default:
                    this.BeginInvoke(AlarmInfo, "Unknow alarm");
                    break;
            }
        }

        private void ProcessCommAlarm_V30(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            MyDebugInfo AlarmInfo = new MyDebugInfo(DebugInfo);
            CHCNetSDK.NET_DVR_ALARMINFO_V30 struAlarmInfoV30 = new CHCNetSDK.NET_DVR_ALARMINFO_V30();

            struAlarmInfoV30 = (CHCNetSDK.NET_DVR_ALARMINFO_V30)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_ALARMINFO_V30));

            string str;
            switch (struAlarmInfoV30.dwAlarmType)
            {
                case 0:
                    this.BeginInvoke(AlarmInfo, "sensor alarm");
                    break;
                case 1:
                    this.BeginInvoke(AlarmInfo, "hard disk full");
                    break;
                case 2:
                    this.BeginInvoke(AlarmInfo, "video lost");
                    break;
                case 3:
                    str = "";
                    str += pAlarmer.sDeviceIP;
                    str += " motion detection";
                    this.BeginInvoke(AlarmInfo, str);
                    break;
                case 4:
                    this.BeginInvoke(AlarmInfo, "hard disk unformatted");
                    break;
                case 5:
                    this.BeginInvoke(AlarmInfo, "hard disk error");
                    break;
                case 6:
                    this.BeginInvoke(AlarmInfo, "tampering detection");
                    break;
                case 7:
                    this.BeginInvoke(AlarmInfo, "unmatched video output standard");
                    break;
                case 8:
                    this.BeginInvoke(AlarmInfo, "illegal operation");
                    break;
                case 9:
                    this.BeginInvoke(AlarmInfo, "videl Signal abnormal");
                    break;
                case 10:
                    this.BeginInvoke(AlarmInfo, "record abnormal");
                    break;
                default:
                    this.BeginInvoke(AlarmInfo, "Unknow alarm");
                    break;
            }
  
        }
        private void Form1_Load(object sender, System.EventArgs e)
        {
        
        }

        private void RealPlayWnd_Click(object sender, EventArgs e)
        {

        }

        private void btnJpegCapture_Click(object sender, EventArgs e)
        {
            m_bJpegCapture = true;  
            IntPtr ptrJpeg = new IntPtr();
            uint nBuffersize =2 * 1024 * 1024;
            ptrJpeg = Marshal.AllocHGlobal((int)nBuffersize);
            uint dwJpegSize = 0;
            
            if (PlayCtrl.PlayM4_GetJPEG(m_lPort, ptrJpeg, nBuffersize, ref dwJpegSize))
            {
                DebugInfo("PlayM4_GetJPEG succ");
            }
            else
            {
                uint dwErrorNo = PlayCtrl.PlayM4_GetLastError(m_lPort);
                DebugInfo("PlayM4_GetJPEG fail");
            }
            FileStream fs = new FileStream("C:/GetJpegSave.jpg", FileMode.Create);
            byte[] by = new byte[dwJpegSize];
            Marshal.Copy(ptrJpeg, by, 0, (int)dwJpegSize);
            fs.Write(by, 0, (int)dwJpegSize);
            fs.Close();

            Marshal.FreeHGlobal(ptrJpeg);
            //public static extern bool PlayM4_GetJPEG(int nPort, ref byte pJpeg, uint nBufSize, ref uint pJpegSize);
        }

        private void btnPreviewType_Click(object sender, EventArgs e)
        {
            if (m_iPreviewType == 0)
            {
                btnPreviewType.Text = "RealPlay Dec";
                m_iPreviewType = 1;
            }
            else
            {
                m_iPreviewType = 0;
                btnPreviewType.Text = "CallBack Dec";
            }
        }

        public delegate void MyDebugInfo(string str);
        public void DebugInfo(string str)
        {
            if (str.Length > 0)
            {
                str += "\n";
                TextBoxInfo.AppendText(str);
            }

        }


        private void btnFortify_Click(object sender, EventArgs e)
        {
            if (m_bGuard)
            {
                if (m_lFortifyHandle != -1)
                {
                    if (CHCNetSDK.NET_DVR_CloseAlarmChan_V30(m_lFortifyHandle))
                    {
                        DebugInfo("NET_DVR_CloseAlarmChan_V30 Succ");
                        btnFortify.Text = "Guard";
                        m_bGuard = !m_bGuard;
                    }
                    else
                    {
                        DebugInfo("NET_DVR_CloseAlarmChan_V30 Fail");
                    }
                }

            }
            else
            {
                m_lFortifyHandle = CHCNetSDK.NET_DVR_SetupAlarmChan_V30(m_lUserID);
                if (m_lFortifyHandle != -1)
                {
                    btnFortify.Text = "Unguard";
                    m_bGuard = !m_bGuard;
                    DebugInfo("NET_DVR_SetupAlarmChan_V30 Succ");
                }
                else
                {
                    DebugInfo("NET_DVR_SetupAlarmChan_V30 Succ");
                }


                m_falarmData = new CHCNetSDK.MSGCallBack(MsgCallback);
                if (CHCNetSDK.NET_DVR_SetDVRMessageCallBack_V30(m_falarmData, IntPtr.Zero))
                {
                    DebugInfo("NET_DVR_SetDVRMessageCallBack_V30 Succ");
                }
                else
                {
                    uint i = CHCNetSDK.NET_DVR_GetLastError();
                    DebugInfo("NET_DVR_SetDVRMessageCallBack_V30 Fail");
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MotionDetect dlg = new MotionDetect();
            dlg.m_lUserID = m_lUserID;
            dlg.m_struDeviceInfo = m_struDeviceInfo;
            dlg.m_lChannel = 1; 
            dlg.ShowDialog();
        }

        private void btnVoiceTalk_Click(object sender, EventArgs e)
        {
            VoiceTalk dlg = new VoiceTalk();
            dlg.m_lUserID = m_lUserID;
            dlg.m_dwAudioChanNum = m_struDeviceInfo.byAudioChanNum;
            dlg.ShowDialog();
        }

        private void btnAlarmConfig_Click(object sender, EventArgs e)
        {
            AlarmConfig dlg = new AlarmConfig();
            dlg.m_lUserID = m_lUserID;
            dlg.m_iAlarmInNum = m_struDeviceInfo.byAlarmInPortNum;
            dlg.m_iAlarmOutNum = m_struDeviceInfo.byAlarmOutPortNum;
            dlg.ShowDialog();
        }

        private void btnOpenSound_Click(object sender, EventArgs e)
        {
                 //   private Int32 m_iPreviewType = 0;
            if (m_lRealHandle < 0)
            {
                MessageBox.Show("Please preview first");
            }
            else
            {
                if (m_iPreviewType == 0) //  callback
                {
                    if (!m_bOpenSound)
                    {
                        if (PlayCtrl.PlayM4_PlaySound(m_lPort))
                        {
                            m_bOpenSound = true;
                            btnOpenSound.Text = "Stop sound";
                        }
                        else
                        {
                            Debug.Print("Fail to open sound");
                        }
                    }
                    else
                    {
                        if (PlayCtrl.PlayM4_StopSound())
                        {
                            m_bOpenSound = false;
                            btnOpenSound.Text = "Open sound";
                        }
                    }
                }
                else                      // Sdk decode
                {
                    if (!m_bOpenSound)
                    {
                        if (CHCNetSDK.NET_DVR_OpenSound(m_lRealHandle))
                        {
                            m_bOpenSound = true;
                            btnOpenSound.Text = "Stop sound";
                        }
                        else
                        {
                            Debug.Print("Fail to open sound");
                        }
                    }
                    else
                    {
                        if (CHCNetSDK.NET_DVR_CloseSound())
                        {
                            m_bOpenSound = false;
                            btnOpenSound.Text = "Open sound";
                        }
                    }
                }
            }
        }

        private void btnPtzCtrl_Click(object sender, EventArgs e)
        {
            PTZCtrl dlg = new PTZCtrl();
            dlg.m_lUserID = m_lUserID;
            dlg.m_lChannel = 1;
            dlg.m_lRealHandle = m_lRealHandle;
            dlg.ShowDialog();
        }
    }
}
