﻿
namespace PreviewDemo
{
    partial class MotionDetect
    {
        public int m_lUserID;
        public int m_lChannel;
        public CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo;
        private CHCNetSDK.DRAWFUN m_fMotionDraw = null;
        private CHCNetSDK.NET_DVR_PICCFG_V30 m_struPicCfgV30;
        private CHCNetSDK.NET_DVR_MOTION_V30 m_struMotionV30;
        private int m_lMotionPlayHandle = -1;

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.comboBoxMotionSensitive = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.treeViewRecordChan = new System.Windows.Forms.TreeView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.checkBoxTriggerAlarm = new System.Windows.Forms.CheckBox();
            this.treeViewAlarmOut = new System.Windows.Forms.TreeView();
            this.checkBoxEmailAlarm = new System.Windows.Forms.CheckBox();
            this.checkBoxReportAlarm = new System.Windows.Forms.CheckBox();
            this.checkBoxAudioAlarm = new System.Windows.Forms.CheckBox();
            this.checkBoxShowAlarm = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnMotionDayCopy = new System.Windows.Forms.Button();
            this.comboBoxWeekdayCopy = new System.Windows.Forms.ComboBox();
            this.btnMotionDayOk = new System.Windows.Forms.Button();
            this.label52 = new System.Windows.Forms.Label();
            this.label51 = new System.Windows.Forms.Label();
            this.label39 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label50 = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label49 = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label48 = new System.Windows.Forms.Label();
            this.label36 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label47 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label46 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label45 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label44 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label43 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label42 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxMin82 = new System.Windows.Forms.TextBox();
            this.textBoxMin62 = new System.Windows.Forms.TextBox();
            this.textBoxMin42 = new System.Windows.Forms.TextBox();
            this.textBoxMin22 = new System.Windows.Forms.TextBox();
            this.textBoxMin72 = new System.Windows.Forms.TextBox();
            this.textBoxMin52 = new System.Windows.Forms.TextBox();
            this.textBoxMin32 = new System.Windows.Forms.TextBox();
            this.textBoxMin12 = new System.Windows.Forms.TextBox();
            this.textBoxHour82 = new System.Windows.Forms.TextBox();
            this.textBoxHour62 = new System.Windows.Forms.TextBox();
            this.textBoxHour42 = new System.Windows.Forms.TextBox();
            this.textBoxHour22 = new System.Windows.Forms.TextBox();
            this.textBoxHour72 = new System.Windows.Forms.TextBox();
            this.textBoxHour52 = new System.Windows.Forms.TextBox();
            this.textBoxHour32 = new System.Windows.Forms.TextBox();
            this.textBoxHour12 = new System.Windows.Forms.TextBox();
            this.textBoxMin81 = new System.Windows.Forms.TextBox();
            this.textBoxHour81 = new System.Windows.Forms.TextBox();
            this.textBoxMin61 = new System.Windows.Forms.TextBox();
            this.textBoxHour61 = new System.Windows.Forms.TextBox();
            this.textBoxMin41 = new System.Windows.Forms.TextBox();
            this.textBoxMin71 = new System.Windows.Forms.TextBox();
            this.textBoxHour41 = new System.Windows.Forms.TextBox();
            this.textBoxMin51 = new System.Windows.Forms.TextBox();
            this.textBoxMin21 = new System.Windows.Forms.TextBox();
            this.label41 = new System.Windows.Forms.Label();
            this.textBoxMin31 = new System.Windows.Forms.TextBox();
            this.label29 = new System.Windows.Forms.Label();
            this.textBoxHour21 = new System.Windows.Forms.TextBox();
            this.textBoxHour71 = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.textBoxHour51 = new System.Windows.Forms.TextBox();
            this.textBoxMin11 = new System.Windows.Forms.TextBox();
            this.label40 = new System.Windows.Forms.Label();
            this.textBoxHour31 = new System.Windows.Forms.TextBox();
            this.label28 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.textBoxHour11 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxWeekday = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnMotionSetup = new System.Windows.Forms.Button();
            this.MotionRealPlay = new System.Windows.Forms.PictureBox();
            this.checkBoxMotionScope = new System.Windows.Forms.CheckBox();
            this.checkBoxEnableMotion = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MotionRealPlay)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBoxMotionSensitive
            // 
            this.comboBoxMotionSensitive.FormattingEnabled = true;
            this.comboBoxMotionSensitive.Items.AddRange(new object[] {
            "Off",
            "0--Lowest",
            "1",
            "2",
            "3",
            "4",
            "5--Highest"});
            this.comboBoxMotionSensitive.Location = new System.Drawing.Point(97, 435);
            this.comboBoxMotionSensitive.Name = "comboBoxMotionSensitive";
            this.comboBoxMotionSensitive.Size = new System.Drawing.Size(84, 20);
            this.comboBoxMotionSensitive.TabIndex = 0;
            this.comboBoxMotionSensitive.SelectedIndexChanged += new System.EventHandler(this.comboBoxMotionSensitive_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 439);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Sensitivity\t";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 12);
            this.label2.TabIndex = 3;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.treeViewRecordChan);
            this.groupBox1.Location = new System.Drawing.Point(490, 193);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(255, 147);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Channel Triggered to Record";
            // 
            // treeViewRecordChan
            // 
            this.treeViewRecordChan.CheckBoxes = true;
            this.treeViewRecordChan.Location = new System.Drawing.Point(37, 23);
            this.treeViewRecordChan.Name = "treeViewRecordChan";
            this.treeViewRecordChan.Size = new System.Drawing.Size(179, 112);
            this.treeViewRecordChan.TabIndex = 1;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.checkBoxTriggerAlarm);
            this.groupBox2.Controls.Add(this.treeViewAlarmOut);
            this.groupBox2.Controls.Add(this.checkBoxEmailAlarm);
            this.groupBox2.Controls.Add(this.checkBoxReportAlarm);
            this.groupBox2.Controls.Add(this.checkBoxAudioAlarm);
            this.groupBox2.Controls.Add(this.checkBoxShowAlarm);
            this.groupBox2.Location = new System.Drawing.Point(490, 31);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(277, 156);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Alarm Handling Mode";
            // 
            // checkBoxTriggerAlarm
            // 
            this.checkBoxTriggerAlarm.AutoSize = true;
            this.checkBoxTriggerAlarm.Location = new System.Drawing.Point(116, 29);
            this.checkBoxTriggerAlarm.Name = "checkBoxTriggerAlarm";
            this.checkBoxTriggerAlarm.Size = new System.Drawing.Size(150, 16);
            this.checkBoxTriggerAlarm.TabIndex = 0;
            this.checkBoxTriggerAlarm.Text = "Trigger Alarm Output:";
            this.checkBoxTriggerAlarm.UseVisualStyleBackColor = true;
            this.checkBoxTriggerAlarm.CheckedChanged += new System.EventHandler(this.checkBoxTriggerAlarm_CheckedChanged);
            // 
            // treeViewAlarmOut
            // 
            this.treeViewAlarmOut.CheckBoxes = true;
            this.treeViewAlarmOut.Location = new System.Drawing.Point(124, 63);
            this.treeViewAlarmOut.Name = "treeViewAlarmOut";
            this.treeViewAlarmOut.Size = new System.Drawing.Size(142, 87);
            this.treeViewAlarmOut.TabIndex = 1;
            // 
            // checkBoxEmailAlarm
            // 
            this.checkBoxEmailAlarm.AutoSize = true;
            this.checkBoxEmailAlarm.Location = new System.Drawing.Point(22, 134);
            this.checkBoxEmailAlarm.Name = "checkBoxEmailAlarm";
            this.checkBoxEmailAlarm.Size = new System.Drawing.Size(84, 16);
            this.checkBoxEmailAlarm.TabIndex = 0;
            this.checkBoxEmailAlarm.Text = "Email JPEG";
            this.checkBoxEmailAlarm.UseVisualStyleBackColor = true;
            // 
            // checkBoxReportAlarm
            // 
            this.checkBoxReportAlarm.AutoSize = true;
            this.checkBoxReportAlarm.Location = new System.Drawing.Point(22, 101);
            this.checkBoxReportAlarm.Name = "checkBoxReportAlarm";
            this.checkBoxReportAlarm.Size = new System.Drawing.Size(96, 16);
            this.checkBoxReportAlarm.TabIndex = 0;
            this.checkBoxReportAlarm.Text = "Report Alarm";
            this.checkBoxReportAlarm.UseVisualStyleBackColor = true;
            // 
            // checkBoxAudioAlarm
            // 
            this.checkBoxAudioAlarm.AutoSize = true;
            this.checkBoxAudioAlarm.Location = new System.Drawing.Point(22, 63);
            this.checkBoxAudioAlarm.Name = "checkBoxAudioAlarm";
            this.checkBoxAudioAlarm.Size = new System.Drawing.Size(90, 16);
            this.checkBoxAudioAlarm.TabIndex = 0;
            this.checkBoxAudioAlarm.Text = "Audio Alarm";
            this.checkBoxAudioAlarm.UseVisualStyleBackColor = true;
            // 
            // checkBoxShowAlarm
            // 
            this.checkBoxShowAlarm.AutoSize = true;
            this.checkBoxShowAlarm.Location = new System.Drawing.Point(22, 29);
            this.checkBoxShowAlarm.Name = "checkBoxShowAlarm";
            this.checkBoxShowAlarm.Size = new System.Drawing.Size(84, 16);
            this.checkBoxShowAlarm.TabIndex = 0;
            this.checkBoxShowAlarm.Text = "Show Alarm";
            this.checkBoxShowAlarm.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnMotionDayCopy);
            this.groupBox3.Controls.Add(this.comboBoxWeekdayCopy);
            this.groupBox3.Controls.Add(this.btnMotionDayOk);
            this.groupBox3.Controls.Add(this.label52);
            this.groupBox3.Controls.Add(this.label51);
            this.groupBox3.Controls.Add(this.label39);
            this.groupBox3.Controls.Add(this.label27);
            this.groupBox3.Controls.Add(this.label15);
            this.groupBox3.Controls.Add(this.label50);
            this.groupBox3.Controls.Add(this.label38);
            this.groupBox3.Controls.Add(this.label26);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label49);
            this.groupBox3.Controls.Add(this.label37);
            this.groupBox3.Controls.Add(this.label25);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.label48);
            this.groupBox3.Controls.Add(this.label36);
            this.groupBox3.Controls.Add(this.label24);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label47);
            this.groupBox3.Controls.Add(this.label35);
            this.groupBox3.Controls.Add(this.label23);
            this.groupBox3.Controls.Add(this.label13);
            this.groupBox3.Controls.Add(this.label46);
            this.groupBox3.Controls.Add(this.label34);
            this.groupBox3.Controls.Add(this.label22);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.label45);
            this.groupBox3.Controls.Add(this.label33);
            this.groupBox3.Controls.Add(this.label21);
            this.groupBox3.Controls.Add(this.label12);
            this.groupBox3.Controls.Add(this.label44);
            this.groupBox3.Controls.Add(this.label32);
            this.groupBox3.Controls.Add(this.label20);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label43);
            this.groupBox3.Controls.Add(this.label31);
            this.groupBox3.Controls.Add(this.label19);
            this.groupBox3.Controls.Add(this.label11);
            this.groupBox3.Controls.Add(this.label42);
            this.groupBox3.Controls.Add(this.label30);
            this.groupBox3.Controls.Add(this.label18);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.textBoxMin82);
            this.groupBox3.Controls.Add(this.textBoxMin62);
            this.groupBox3.Controls.Add(this.textBoxMin42);
            this.groupBox3.Controls.Add(this.textBoxMin22);
            this.groupBox3.Controls.Add(this.textBoxMin72);
            this.groupBox3.Controls.Add(this.textBoxMin52);
            this.groupBox3.Controls.Add(this.textBoxMin32);
            this.groupBox3.Controls.Add(this.textBoxMin12);
            this.groupBox3.Controls.Add(this.textBoxHour82);
            this.groupBox3.Controls.Add(this.textBoxHour62);
            this.groupBox3.Controls.Add(this.textBoxHour42);
            this.groupBox3.Controls.Add(this.textBoxHour22);
            this.groupBox3.Controls.Add(this.textBoxHour72);
            this.groupBox3.Controls.Add(this.textBoxHour52);
            this.groupBox3.Controls.Add(this.textBoxHour32);
            this.groupBox3.Controls.Add(this.textBoxHour12);
            this.groupBox3.Controls.Add(this.textBoxMin81);
            this.groupBox3.Controls.Add(this.textBoxHour81);
            this.groupBox3.Controls.Add(this.textBoxMin61);
            this.groupBox3.Controls.Add(this.textBoxHour61);
            this.groupBox3.Controls.Add(this.textBoxMin41);
            this.groupBox3.Controls.Add(this.textBoxMin71);
            this.groupBox3.Controls.Add(this.textBoxHour41);
            this.groupBox3.Controls.Add(this.textBoxMin51);
            this.groupBox3.Controls.Add(this.textBoxMin21);
            this.groupBox3.Controls.Add(this.label41);
            this.groupBox3.Controls.Add(this.textBoxMin31);
            this.groupBox3.Controls.Add(this.label29);
            this.groupBox3.Controls.Add(this.textBoxHour21);
            this.groupBox3.Controls.Add(this.textBoxHour71);
            this.groupBox3.Controls.Add(this.label17);
            this.groupBox3.Controls.Add(this.textBoxHour51);
            this.groupBox3.Controls.Add(this.textBoxMin11);
            this.groupBox3.Controls.Add(this.label40);
            this.groupBox3.Controls.Add(this.textBoxHour31);
            this.groupBox3.Controls.Add(this.label28);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label16);
            this.groupBox3.Controls.Add(this.textBoxHour11);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.comboBoxWeekday);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Location = new System.Drawing.Point(204, 340);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(563, 217);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Guard time:";
            this.groupBox3.Enter += new System.EventHandler(this.groupBox3_Enter);
            // 
            // btnMotionDayCopy
            // 
            this.btnMotionDayCopy.Location = new System.Drawing.Point(417, 185);
            this.btnMotionDayCopy.Name = "btnMotionDayCopy";
            this.btnMotionDayCopy.Size = new System.Drawing.Size(55, 21);
            this.btnMotionDayCopy.TabIndex = 9;
            this.btnMotionDayCopy.Text = "Copy";
            this.btnMotionDayCopy.UseVisualStyleBackColor = true;
            this.btnMotionDayCopy.Click += new System.EventHandler(this.btnMotionDayCopy_Click);
            // 
            // comboBoxWeekdayCopy
            // 
            this.comboBoxWeekdayCopy.FormattingEnabled = true;
            this.comboBoxWeekdayCopy.Items.AddRange(new object[] {
            "Whole",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"});
            this.comboBoxWeekdayCopy.Location = new System.Drawing.Point(330, 183);
            this.comboBoxWeekdayCopy.Name = "comboBoxWeekdayCopy";
            this.comboBoxWeekdayCopy.Size = new System.Drawing.Size(78, 20);
            this.comboBoxWeekdayCopy.TabIndex = 8;
            // 
            // btnMotionDayOk
            // 
            this.btnMotionDayOk.Location = new System.Drawing.Point(478, 187);
            this.btnMotionDayOk.Name = "btnMotionDayOk";
            this.btnMotionDayOk.Size = new System.Drawing.Size(77, 21);
            this.btnMotionDayOk.TabIndex = 7;
            this.btnMotionDayOk.Text = "Comfirm";
            this.btnMotionDayOk.UseVisualStyleBackColor = true;
            this.btnMotionDayOk.Click += new System.EventHandler(this.btnMotionDayOk_Click);
            // 
            // label52
            // 
            this.label52.AutoSize = true;
            this.label52.Location = new System.Drawing.Point(258, 184);
            this.label52.Name = "label52";
            this.label52.Size = new System.Drawing.Size(47, 12);
            this.label52.TabIndex = 6;
            this.label52.Text = "Copy to";
            // 
            // label51
            // 
            this.label51.AutoSize = true;
            this.label51.Location = new System.Drawing.Point(432, 148);
            this.label51.Name = "label51";
            this.label51.Size = new System.Drawing.Size(17, 12);
            this.label51.TabIndex = 5;
            this.label51.Text = "--";
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Location = new System.Drawing.Point(432, 121);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(17, 12);
            this.label39.TabIndex = 5;
            this.label39.Text = "--";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(432, 94);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(17, 12);
            this.label27.TabIndex = 5;
            this.label27.Text = "--";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(433, 67);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(17, 12);
            this.label15.TabIndex = 5;
            this.label15.Text = "--";
            // 
            // label50
            // 
            this.label50.AutoSize = true;
            this.label50.Location = new System.Drawing.Point(159, 148);
            this.label50.Name = "label50";
            this.label50.Size = new System.Drawing.Size(17, 12);
            this.label50.TabIndex = 5;
            this.label50.Text = "--";
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(159, 121);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(17, 12);
            this.label38.TabIndex = 5;
            this.label38.Text = "--";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(159, 94);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(17, 12);
            this.label26.TabIndex = 5;
            this.label26.Text = "--";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(160, 67);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 12);
            this.label9.TabIndex = 5;
            this.label9.Text = "--";
            // 
            // label49
            // 
            this.label49.AutoSize = true;
            this.label49.Location = new System.Drawing.Point(528, 148);
            this.label49.Name = "label49";
            this.label49.Size = new System.Drawing.Size(11, 12);
            this.label49.TabIndex = 4;
            this.label49.Text = "M";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(528, 121);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(11, 12);
            this.label37.TabIndex = 4;
            this.label37.Text = "M";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(528, 94);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(11, 12);
            this.label25.TabIndex = 4;
            this.label25.Text = "M";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(529, 67);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(11, 12);
            this.label14.TabIndex = 4;
            this.label14.Text = "M";
            // 
            // label48
            // 
            this.label48.AutoSize = true;
            this.label48.Location = new System.Drawing.Point(255, 148);
            this.label48.Name = "label48";
            this.label48.Size = new System.Drawing.Size(11, 12);
            this.label48.TabIndex = 4;
            this.label48.Text = "M";
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(255, 121);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(11, 12);
            this.label36.TabIndex = 4;
            this.label36.Text = "M";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(255, 94);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(11, 12);
            this.label24.TabIndex = 4;
            this.label24.Text = "M";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(256, 67);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(11, 12);
            this.label8.TabIndex = 4;
            this.label8.Text = "M";
            // 
            // label47
            // 
            this.label47.AutoSize = true;
            this.label47.Location = new System.Drawing.Point(483, 148);
            this.label47.Name = "label47";
            this.label47.Size = new System.Drawing.Size(11, 12);
            this.label47.TabIndex = 4;
            this.label47.Text = "H";
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(483, 121);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(11, 12);
            this.label35.TabIndex = 4;
            this.label35.Text = "H";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(483, 94);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(11, 12);
            this.label23.TabIndex = 4;
            this.label23.Text = "H";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(484, 67);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(11, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "H";
            // 
            // label46
            // 
            this.label46.AutoSize = true;
            this.label46.Location = new System.Drawing.Point(210, 148);
            this.label46.Name = "label46";
            this.label46.Size = new System.Drawing.Size(11, 12);
            this.label46.TabIndex = 4;
            this.label46.Text = "H";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(210, 121);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(11, 12);
            this.label34.TabIndex = 4;
            this.label34.Text = "H";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(210, 94);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(11, 12);
            this.label22.TabIndex = 4;
            this.label22.Text = "H";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(211, 67);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(11, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "H";
            // 
            // label45
            // 
            this.label45.AutoSize = true;
            this.label45.Location = new System.Drawing.Point(423, 148);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(11, 12);
            this.label45.TabIndex = 4;
            this.label45.Text = "M";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(423, 121);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(11, 12);
            this.label33.TabIndex = 4;
            this.label33.Text = "M";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(423, 94);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(11, 12);
            this.label21.TabIndex = 4;
            this.label21.Text = "M";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(424, 67);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(11, 12);
            this.label12.TabIndex = 4;
            this.label12.Text = "M";
            // 
            // label44
            // 
            this.label44.AutoSize = true;
            this.label44.Location = new System.Drawing.Point(150, 148);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(11, 12);
            this.label44.TabIndex = 4;
            this.label44.Text = "M";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(150, 121);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(11, 12);
            this.label32.TabIndex = 4;
            this.label32.Text = "M";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(150, 94);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(11, 12);
            this.label20.TabIndex = 4;
            this.label20.Text = "M";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(151, 67);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(11, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "M";
            // 
            // label43
            // 
            this.label43.AutoSize = true;
            this.label43.Location = new System.Drawing.Point(378, 148);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(11, 12);
            this.label43.TabIndex = 4;
            this.label43.Text = "H";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(378, 121);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(11, 12);
            this.label31.TabIndex = 4;
            this.label31.Text = "H";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(378, 94);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(11, 12);
            this.label19.TabIndex = 4;
            this.label19.Text = "H";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(379, 67);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(11, 12);
            this.label11.TabIndex = 4;
            this.label11.Text = "H";
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Location = new System.Drawing.Point(105, 148);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(11, 12);
            this.label42.TabIndex = 4;
            this.label42.Text = "H";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(105, 121);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(11, 12);
            this.label30.TabIndex = 4;
            this.label30.Text = "H";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(105, 94);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(11, 12);
            this.label18.TabIndex = 4;
            this.label18.Text = "H";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(106, 67);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(11, 12);
            this.label5.TabIndex = 4;
            this.label5.Text = "H";
            // 
            // textBoxMin82
            // 
            this.textBoxMin82.Location = new System.Drawing.Point(499, 144);
            this.textBoxMin82.Name = "textBoxMin82";
            this.textBoxMin82.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin82.TabIndex = 3;
            // 
            // textBoxMin62
            // 
            this.textBoxMin62.Location = new System.Drawing.Point(499, 117);
            this.textBoxMin62.Name = "textBoxMin62";
            this.textBoxMin62.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin62.TabIndex = 3;
            // 
            // textBoxMin42
            // 
            this.textBoxMin42.Location = new System.Drawing.Point(499, 90);
            this.textBoxMin42.Name = "textBoxMin42";
            this.textBoxMin42.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin42.TabIndex = 3;
            // 
            // textBoxMin22
            // 
            this.textBoxMin22.Location = new System.Drawing.Point(500, 63);
            this.textBoxMin22.Name = "textBoxMin22";
            this.textBoxMin22.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin22.TabIndex = 3;
            // 
            // textBoxMin72
            // 
            this.textBoxMin72.Location = new System.Drawing.Point(226, 144);
            this.textBoxMin72.Name = "textBoxMin72";
            this.textBoxMin72.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin72.TabIndex = 3;
            // 
            // textBoxMin52
            // 
            this.textBoxMin52.Location = new System.Drawing.Point(226, 117);
            this.textBoxMin52.Name = "textBoxMin52";
            this.textBoxMin52.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin52.TabIndex = 3;
            // 
            // textBoxMin32
            // 
            this.textBoxMin32.Location = new System.Drawing.Point(226, 90);
            this.textBoxMin32.Name = "textBoxMin32";
            this.textBoxMin32.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin32.TabIndex = 3;
            // 
            // textBoxMin12
            // 
            this.textBoxMin12.Location = new System.Drawing.Point(227, 63);
            this.textBoxMin12.Name = "textBoxMin12";
            this.textBoxMin12.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin12.TabIndex = 3;
            // 
            // textBoxHour82
            // 
            this.textBoxHour82.Location = new System.Drawing.Point(454, 144);
            this.textBoxHour82.Name = "textBoxHour82";
            this.textBoxHour82.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour82.TabIndex = 3;
            // 
            // textBoxHour62
            // 
            this.textBoxHour62.Location = new System.Drawing.Point(454, 117);
            this.textBoxHour62.Name = "textBoxHour62";
            this.textBoxHour62.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour62.TabIndex = 3;
            // 
            // textBoxHour42
            // 
            this.textBoxHour42.Location = new System.Drawing.Point(454, 90);
            this.textBoxHour42.Name = "textBoxHour42";
            this.textBoxHour42.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour42.TabIndex = 3;
            // 
            // textBoxHour22
            // 
            this.textBoxHour22.Location = new System.Drawing.Point(455, 63);
            this.textBoxHour22.Name = "textBoxHour22";
            this.textBoxHour22.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour22.TabIndex = 3;
            // 
            // textBoxHour72
            // 
            this.textBoxHour72.Location = new System.Drawing.Point(181, 144);
            this.textBoxHour72.Name = "textBoxHour72";
            this.textBoxHour72.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour72.TabIndex = 3;
            // 
            // textBoxHour52
            // 
            this.textBoxHour52.Location = new System.Drawing.Point(181, 117);
            this.textBoxHour52.Name = "textBoxHour52";
            this.textBoxHour52.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour52.TabIndex = 3;
            // 
            // textBoxHour32
            // 
            this.textBoxHour32.Location = new System.Drawing.Point(181, 90);
            this.textBoxHour32.Name = "textBoxHour32";
            this.textBoxHour32.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour32.TabIndex = 3;
            // 
            // textBoxHour12
            // 
            this.textBoxHour12.Location = new System.Drawing.Point(181, 63);
            this.textBoxHour12.Name = "textBoxHour12";
            this.textBoxHour12.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour12.TabIndex = 3;
            // 
            // textBoxMin81
            // 
            this.textBoxMin81.Location = new System.Drawing.Point(394, 144);
            this.textBoxMin81.Name = "textBoxMin81";
            this.textBoxMin81.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin81.TabIndex = 3;
            // 
            // textBoxHour81
            // 
            this.textBoxHour81.Location = new System.Drawing.Point(349, 144);
            this.textBoxHour81.Name = "textBoxHour81";
            this.textBoxHour81.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour81.TabIndex = 3;
            // 
            // textBoxMin61
            // 
            this.textBoxMin61.Location = new System.Drawing.Point(394, 117);
            this.textBoxMin61.Name = "textBoxMin61";
            this.textBoxMin61.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin61.TabIndex = 3;
            // 
            // textBoxHour61
            // 
            this.textBoxHour61.Location = new System.Drawing.Point(349, 117);
            this.textBoxHour61.Name = "textBoxHour61";
            this.textBoxHour61.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour61.TabIndex = 3;
            // 
            // textBoxMin41
            // 
            this.textBoxMin41.Location = new System.Drawing.Point(394, 90);
            this.textBoxMin41.Name = "textBoxMin41";
            this.textBoxMin41.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin41.TabIndex = 3;
            // 
            // textBoxMin71
            // 
            this.textBoxMin71.Location = new System.Drawing.Point(121, 144);
            this.textBoxMin71.Name = "textBoxMin71";
            this.textBoxMin71.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin71.TabIndex = 3;
            // 
            // textBoxHour41
            // 
            this.textBoxHour41.Location = new System.Drawing.Point(349, 90);
            this.textBoxHour41.Name = "textBoxHour41";
            this.textBoxHour41.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour41.TabIndex = 3;
            // 
            // textBoxMin51
            // 
            this.textBoxMin51.Location = new System.Drawing.Point(121, 117);
            this.textBoxMin51.Name = "textBoxMin51";
            this.textBoxMin51.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin51.TabIndex = 3;
            // 
            // textBoxMin21
            // 
            this.textBoxMin21.Location = new System.Drawing.Point(395, 63);
            this.textBoxMin21.Name = "textBoxMin21";
            this.textBoxMin21.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin21.TabIndex = 3;
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(297, 148);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(47, 12);
            this.label41.TabIndex = 2;
            this.label41.Text = "Period8";
            // 
            // textBoxMin31
            // 
            this.textBoxMin31.Location = new System.Drawing.Point(121, 90);
            this.textBoxMin31.Name = "textBoxMin31";
            this.textBoxMin31.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin31.TabIndex = 3;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(297, 121);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(47, 12);
            this.label29.TabIndex = 2;
            this.label29.Text = "Period6";
            // 
            // textBoxHour21
            // 
            this.textBoxHour21.Location = new System.Drawing.Point(350, 63);
            this.textBoxHour21.Name = "textBoxHour21";
            this.textBoxHour21.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour21.TabIndex = 3;
            // 
            // textBoxHour71
            // 
            this.textBoxHour71.Location = new System.Drawing.Point(76, 144);
            this.textBoxHour71.Name = "textBoxHour71";
            this.textBoxHour71.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour71.TabIndex = 3;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(297, 94);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(47, 12);
            this.label17.TabIndex = 2;
            this.label17.Text = "Period4";
            // 
            // textBoxHour51
            // 
            this.textBoxHour51.Location = new System.Drawing.Point(76, 117);
            this.textBoxHour51.Name = "textBoxHour51";
            this.textBoxHour51.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour51.TabIndex = 3;
            // 
            // textBoxMin11
            // 
            this.textBoxMin11.Location = new System.Drawing.Point(122, 63);
            this.textBoxMin11.Name = "textBoxMin11";
            this.textBoxMin11.Size = new System.Drawing.Size(24, 21);
            this.textBoxMin11.TabIndex = 3;
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Location = new System.Drawing.Point(24, 148);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(47, 12);
            this.label40.TabIndex = 2;
            this.label40.Text = "Period7";
            // 
            // textBoxHour31
            // 
            this.textBoxHour31.Location = new System.Drawing.Point(76, 90);
            this.textBoxHour31.Name = "textBoxHour31";
            this.textBoxHour31.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour31.TabIndex = 3;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(24, 121);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(47, 12);
            this.label28.TabIndex = 2;
            this.label28.Text = "Period5";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(298, 67);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 2;
            this.label10.Text = "Period2";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(24, 94);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(47, 12);
            this.label16.TabIndex = 2;
            this.label16.Text = "Period3";
            // 
            // textBoxHour11
            // 
            this.textBoxHour11.Location = new System.Drawing.Point(77, 63);
            this.textBoxHour11.Name = "textBoxHour11";
            this.textBoxHour11.Size = new System.Drawing.Size(24, 21);
            this.textBoxHour11.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 67);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "Period1";
            // 
            // comboBoxWeekday
            // 
            this.comboBoxWeekday.FormattingEnabled = true;
            this.comboBoxWeekday.Items.AddRange(new object[] {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"});
            this.comboBoxWeekday.Location = new System.Drawing.Point(114, 26);
            this.comboBoxWeekday.Name = "comboBoxWeekday";
            this.comboBoxWeekday.Size = new System.Drawing.Size(103, 20);
            this.comboBoxWeekday.TabIndex = 1;
            this.comboBoxWeekday.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "Date";
            // 
            // btnMotionSetup
            // 
            this.btnMotionSetup.Location = new System.Drawing.Point(690, 556);
            this.btnMotionSetup.Name = "btnMotionSetup";
            this.btnMotionSetup.Size = new System.Drawing.Size(55, 22);
            this.btnMotionSetup.TabIndex = 7;
            this.btnMotionSetup.Text = "Setup";
            this.btnMotionSetup.UseVisualStyleBackColor = true;
            this.btnMotionSetup.Click += new System.EventHandler(this.btnMotionSetup_Click);
            // 
            // MotionRealPlay
            // 
            this.MotionRealPlay.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MotionRealPlay.Location = new System.Drawing.Point(26, 11);
            this.MotionRealPlay.Name = "MotionRealPlay";
            this.MotionRealPlay.Size = new System.Drawing.Size(396, 324);
            this.MotionRealPlay.TabIndex = 8;
            this.MotionRealPlay.TabStop = false;
            // 
            // checkBoxMotionScope
            // 
            this.checkBoxMotionScope.AutoSize = true;
            this.checkBoxMotionScope.Location = new System.Drawing.Point(27, 356);
            this.checkBoxMotionScope.Name = "checkBoxMotionScope";
            this.checkBoxMotionScope.Size = new System.Drawing.Size(132, 16);
            this.checkBoxMotionScope.TabIndex = 9;
            this.checkBoxMotionScope.Text = "whole motion scope";
            this.checkBoxMotionScope.UseVisualStyleBackColor = true;
            // 
            // checkBoxEnableMotion
            // 
            this.checkBoxEnableMotion.AutoSize = true;
            this.checkBoxEnableMotion.Location = new System.Drawing.Point(27, 399);
            this.checkBoxEnableMotion.Name = "checkBoxEnableMotion";
            this.checkBoxEnableMotion.Size = new System.Drawing.Size(96, 16);
            this.checkBoxEnableMotion.TabIndex = 10;
            this.checkBoxEnableMotion.Text = "EnableMotion";
            this.checkBoxEnableMotion.UseVisualStyleBackColor = true;
            // 
            // MotionDetect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(770, 579);
            this.Controls.Add(this.checkBoxEnableMotion);
            this.Controls.Add(this.checkBoxMotionScope);
            this.Controls.Add(this.MotionRealPlay);
            this.Controls.Add(this.btnMotionSetup);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxMotionSensitive);
            this.Name = "MotionDetect";
            this.Text = "MotionDetect";
            this.Load += new System.EventHandler(this.MotionDetect_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MotionDetect_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MotionRealPlay)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxMotionSensitive;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TreeView treeViewRecordChan;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox checkBoxTriggerAlarm;
        private System.Windows.Forms.TreeView treeViewAlarmOut;
        private System.Windows.Forms.CheckBox checkBoxEmailAlarm;
        private System.Windows.Forms.CheckBox checkBoxReportAlarm;
        private System.Windows.Forms.CheckBox checkBoxAudioAlarm;
        private System.Windows.Forms.CheckBox checkBoxShowAlarm;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox comboBoxWeekday;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxMin12;
        private System.Windows.Forms.TextBox textBoxHour12;
        private System.Windows.Forms.TextBox textBoxMin11;
        private System.Windows.Forms.TextBox textBoxHour11;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label51;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label50;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label49;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label48;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label47;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label46;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label45;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label44;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label43;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label42;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox textBoxMin82;
        private System.Windows.Forms.TextBox textBoxMin62;
        private System.Windows.Forms.TextBox textBoxMin42;
        private System.Windows.Forms.TextBox textBoxMin22;
        private System.Windows.Forms.TextBox textBoxMin72;
        private System.Windows.Forms.TextBox textBoxMin52;
        private System.Windows.Forms.TextBox textBoxMin32;
        private System.Windows.Forms.TextBox textBoxHour82;
        private System.Windows.Forms.TextBox textBoxHour62;
        private System.Windows.Forms.TextBox textBoxHour42;
        private System.Windows.Forms.TextBox textBoxHour22;
        private System.Windows.Forms.TextBox textBoxHour72;
        private System.Windows.Forms.TextBox textBoxHour52;
        private System.Windows.Forms.TextBox textBoxHour32;
        private System.Windows.Forms.TextBox textBoxMin81;
        private System.Windows.Forms.TextBox textBoxHour81;
        private System.Windows.Forms.TextBox textBoxMin61;
        private System.Windows.Forms.TextBox textBoxHour61;
        private System.Windows.Forms.TextBox textBoxMin41;
        private System.Windows.Forms.TextBox textBoxMin71;
        private System.Windows.Forms.TextBox textBoxHour41;
        private System.Windows.Forms.TextBox textBoxMin51;
        private System.Windows.Forms.TextBox textBoxMin21;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.TextBox textBoxMin31;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.TextBox textBoxHour21;
        private System.Windows.Forms.TextBox textBoxHour71;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBoxHour51;
        private System.Windows.Forms.Label label40;
        private System.Windows.Forms.TextBox textBoxHour31;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Button btnMotionDayOk;
        private System.Windows.Forms.Label label52;
        private System.Windows.Forms.Button btnMotionDayCopy;
        private System.Windows.Forms.ComboBox comboBoxWeekdayCopy;
        private System.Windows.Forms.Button btnMotionSetup;
        private System.Windows.Forms.PictureBox MotionRealPlay;
        private System.Windows.Forms.CheckBox checkBoxMotionScope;
        private System.Windows.Forms.CheckBox checkBoxEnableMotion;
    }
}