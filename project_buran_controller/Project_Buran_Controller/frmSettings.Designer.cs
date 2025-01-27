namespace Project_Buran_Controller
{
    partial class frmSettings
    {
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
            this.ApplyButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.ConfigGroup = new System.Windows.Forms.GroupBox();
            this.BuranPathTextBox = new System.Windows.Forms.TextBox();
            this.BuranButtonProfileButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.ButtonPathTextBox = new System.Windows.Forms.TextBox();
            this.ButtonPathDescLabel = new System.Windows.Forms.Label();
            this.ButtonProfilePathButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.BuranButtonLabel = new System.Windows.Forms.Label();
            this.BuranStatusDynmaicLabel = new System.Windows.Forms.Label();
            this.BuranStatusLabel = new System.Windows.Forms.Label();
            this.SerialConnectButton = new System.Windows.Forms.Button();
            this.SerialRefreshButton = new System.Windows.Forms.Button();
            this.COMPortComboBox = new System.Windows.Forms.ComboBox();
            this.ConfigGroup.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ApplyButton
            // 
            this.ApplyButton.Location = new System.Drawing.Point(21, 415);
            this.ApplyButton.Name = "ApplyButton";
            this.ApplyButton.Size = new System.Drawing.Size(131, 23);
            this.ApplyButton.TabIndex = 1;
            this.ApplyButton.Text = "Apply";
            this.ApplyButton.UseVisualStyleBackColor = true;
            this.ApplyButton.Click += new System.EventHandler(this.ApplyButton_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(174, 415);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(125, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Close";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ConfigGroup
            // 
            this.ConfigGroup.Controls.Add(this.BuranPathTextBox);
            this.ConfigGroup.Controls.Add(this.BuranButtonProfileButton);
            this.ConfigGroup.Controls.Add(this.label1);
            this.ConfigGroup.Controls.Add(this.ButtonPathTextBox);
            this.ConfigGroup.Controls.Add(this.ButtonPathDescLabel);
            this.ConfigGroup.Controls.Add(this.ButtonProfilePathButton);
            this.ConfigGroup.Location = new System.Drawing.Point(12, 12);
            this.ConfigGroup.Name = "ConfigGroup";
            this.ConfigGroup.Size = new System.Drawing.Size(304, 138);
            this.ConfigGroup.TabIndex = 3;
            this.ConfigGroup.TabStop = false;
            this.ConfigGroup.Text = "Config Files";
            this.ConfigGroup.Enter += new System.EventHandler(this.ConfigGroup_Enter);
            // 
            // BuranPathTextBox
            // 
            this.BuranPathTextBox.Enabled = false;
            this.BuranPathTextBox.Location = new System.Drawing.Point(9, 102);
            this.BuranPathTextBox.Name = "BuranPathTextBox";
            this.BuranPathTextBox.Size = new System.Drawing.Size(278, 20);
            this.BuranPathTextBox.TabIndex = 5;
            // 
            // BuranButtonProfileButton
            // 
            this.BuranButtonProfileButton.Location = new System.Drawing.Point(162, 75);
            this.BuranButtonProfileButton.Name = "BuranButtonProfileButton";
            this.BuranButtonProfileButton.Size = new System.Drawing.Size(125, 21);
            this.BuranButtonProfileButton.TabIndex = 4;
            this.BuranButtonProfileButton.Text = "Change Path";
            this.BuranButtonProfileButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.BuranButtonProfileButton.UseVisualStyleBackColor = true;
            this.BuranButtonProfileButton.Click += new System.EventHandler(this.BuranButtonProfileButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 79);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(132, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Buran Settings Save Path:";
            // 
            // ButtonPathTextBox
            // 
            this.ButtonPathTextBox.Enabled = false;
            this.ButtonPathTextBox.Location = new System.Drawing.Point(9, 49);
            this.ButtonPathTextBox.Name = "ButtonPathTextBox";
            this.ButtonPathTextBox.Size = new System.Drawing.Size(278, 20);
            this.ButtonPathTextBox.TabIndex = 2;
            // 
            // ButtonPathDescLabel
            // 
            this.ButtonPathDescLabel.AutoSize = true;
            this.ButtonPathDescLabel.Location = new System.Drawing.Point(6, 27);
            this.ButtonPathDescLabel.Name = "ButtonPathDescLabel";
            this.ButtonPathDescLabel.Size = new System.Drawing.Size(126, 13);
            this.ButtonPathDescLabel.TabIndex = 1;
            this.ButtonPathDescLabel.Text = "Button Profile Save Path:";
            // 
            // ButtonProfilePathButton
            // 
            this.ButtonProfilePathButton.Location = new System.Drawing.Point(162, 22);
            this.ButtonProfilePathButton.Name = "ButtonProfilePathButton";
            this.ButtonProfilePathButton.Size = new System.Drawing.Size(125, 21);
            this.ButtonProfilePathButton.TabIndex = 0;
            this.ButtonProfilePathButton.Text = "Change Path";
            this.ButtonProfilePathButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.ButtonProfilePathButton.UseVisualStyleBackColor = true;
            this.ButtonProfilePathButton.Click += new System.EventHandler(this.ButtonProfilePathButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.BuranButtonLabel);
            this.groupBox1.Controls.Add(this.BuranStatusDynmaicLabel);
            this.groupBox1.Controls.Add(this.BuranStatusLabel);
            this.groupBox1.Controls.Add(this.SerialConnectButton);
            this.groupBox1.Controls.Add(this.SerialRefreshButton);
            this.groupBox1.Controls.Add(this.COMPortComboBox);
            this.groupBox1.Location = new System.Drawing.Point(12, 156);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(304, 99);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Serial Config";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(252, 72);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "<TBD>";
            // 
            // BuranButtonLabel
            // 
            this.BuranButtonLabel.AutoSize = true;
            this.BuranButtonLabel.Location = new System.Drawing.Point(159, 72);
            this.BuranButtonLabel.Name = "BuranButtonLabel";
            this.BuranButtonLabel.Size = new System.Drawing.Size(97, 13);
            this.BuranButtonLabel.TabIndex = 6;
            this.BuranButtonLabel.Text = "Number of buttons:";
            // 
            // BuranStatusDynmaicLabel
            // 
            this.BuranStatusDynmaicLabel.AutoSize = true;
            this.BuranStatusDynmaicLabel.Location = new System.Drawing.Point(85, 72);
            this.BuranStatusDynmaicLabel.Name = "BuranStatusDynmaicLabel";
            this.BuranStatusDynmaicLabel.Size = new System.Drawing.Size(41, 13);
            this.BuranStatusDynmaicLabel.TabIndex = 7;
            this.BuranStatusDynmaicLabel.Text = "<TBD>";
            // 
            // BuranStatusLabel
            // 
            this.BuranStatusLabel.AutoSize = true;
            this.BuranStatusLabel.Location = new System.Drawing.Point(8, 72);
            this.BuranStatusLabel.Name = "BuranStatusLabel";
            this.BuranStatusLabel.Size = new System.Drawing.Size(71, 13);
            this.BuranStatusLabel.TabIndex = 5;
            this.BuranStatusLabel.Text = "Buran Status:";
            // 
            // SerialConnectButton
            // 
            this.SerialConnectButton.Location = new System.Drawing.Point(9, 46);
            this.SerialConnectButton.Name = "SerialConnectButton";
            this.SerialConnectButton.Size = new System.Drawing.Size(278, 23);
            this.SerialConnectButton.TabIndex = 6;
            this.SerialConnectButton.Text = "Connect";
            this.SerialConnectButton.UseVisualStyleBackColor = true;
            // 
            // SerialRefreshButton
            // 
            this.SerialRefreshButton.Location = new System.Drawing.Point(162, 17);
            this.SerialRefreshButton.Name = "SerialRefreshButton";
            this.SerialRefreshButton.Size = new System.Drawing.Size(125, 23);
            this.SerialRefreshButton.TabIndex = 5;
            this.SerialRefreshButton.Text = "Refresh";
            this.SerialRefreshButton.UseVisualStyleBackColor = true;
            this.SerialRefreshButton.Click += new System.EventHandler(this.button2_Click);
            // 
            // COMPortComboBox
            // 
            this.COMPortComboBox.FormattingEnabled = true;
            this.COMPortComboBox.Location = new System.Drawing.Point(9, 19);
            this.COMPortComboBox.Name = "COMPortComboBox";
            this.COMPortComboBox.Size = new System.Drawing.Size(131, 21);
            this.COMPortComboBox.TabIndex = 0;
            // 
            // frmSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(328, 450);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.ConfigGroup);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.ApplyButton);
            this.Name = "frmSettings";
            this.Text = "frmSettings";
            this.Load += new System.EventHandler(this.frmSettings_Load);
            this.ConfigGroup.ResumeLayout(false);
            this.ConfigGroup.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button ApplyButton;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox ConfigGroup;
        private System.Windows.Forms.TextBox ButtonPathTextBox;
        private System.Windows.Forms.Label ButtonPathDescLabel;
        private System.Windows.Forms.Button ButtonProfilePathButton;
        private System.Windows.Forms.Button BuranButtonProfileButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button SerialConnectButton;
        private System.Windows.Forms.Button SerialRefreshButton;
        private System.Windows.Forms.ComboBox COMPortComboBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label BuranButtonLabel;
        private System.Windows.Forms.Label BuranStatusDynmaicLabel;
        private System.Windows.Forms.Label BuranStatusLabel;
        private System.Windows.Forms.TextBox BuranPathTextBox;
    }
}