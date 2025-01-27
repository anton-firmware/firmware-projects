
namespace Buran_Controller
{
    partial class frmButtonConfig
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
            this.components = new System.ComponentModel.Container();
            this.btnAddButton = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.buttonColorDialog = new System.Windows.Forms.ColorDialog();
            this.button3 = new System.Windows.Forms.Button();
            this.lblButtonColor = new System.Windows.Forms.Label();
            this.tboColorIndicator = new System.Windows.Forms.TextBox();
            this.lblFunction = new System.Windows.Forms.Label();
            this.cboFunction = new System.Windows.Forms.ComboBox();
            this.pnlScene = new System.Windows.Forms.Panel();
            this.cboSceneSelect = new System.Windows.Forms.ComboBox();
            this.lblScene = new System.Windows.Forms.Label();
            this.guiUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.pnlScene.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnAddButton
            // 
            this.btnAddButton.Location = new System.Drawing.Point(12, 215);
            this.btnAddButton.Name = "btnAddButton";
            this.btnAddButton.Size = new System.Drawing.Size(169, 23);
            this.btnAddButton.TabIndex = 0;
            this.btnAddButton.Text = "Add Button";
            this.btnAddButton.UseVisualStyleBackColor = true;
            this.btnAddButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(189, 215);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(169, 23);
            this.btnClose.TabIndex = 1;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(213, 12);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(143, 23);
            this.button3.TabIndex = 2;
            this.button3.Text = "Set Colour";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // lblButtonColor
            // 
            this.lblButtonColor.AutoSize = true;
            this.lblButtonColor.Location = new System.Drawing.Point(9, 17);
            this.lblButtonColor.Name = "lblButtonColor";
            this.lblButtonColor.Size = new System.Drawing.Size(71, 13);
            this.lblButtonColor.TabIndex = 3;
            this.lblButtonColor.Text = "Button Colour";
            // 
            // tboColorIndicator
            // 
            this.tboColorIndicator.Enabled = false;
            this.tboColorIndicator.Location = new System.Drawing.Point(86, 14);
            this.tboColorIndicator.Name = "tboColorIndicator";
            this.tboColorIndicator.ReadOnly = true;
            this.tboColorIndicator.Size = new System.Drawing.Size(121, 20);
            this.tboColorIndicator.TabIndex = 4;
            // 
            // lblFunction
            // 
            this.lblFunction.AutoSize = true;
            this.lblFunction.Location = new System.Drawing.Point(9, 44);
            this.lblFunction.Name = "lblFunction";
            this.lblFunction.Size = new System.Drawing.Size(48, 13);
            this.lblFunction.TabIndex = 5;
            this.lblFunction.Text = "Function";
            this.lblFunction.Click += new System.EventHandler(this.lblFunction_Click);
            // 
            // cboFunction
            // 
            this.cboFunction.FormattingEnabled = true;
            this.cboFunction.Location = new System.Drawing.Point(88, 41);
            this.cboFunction.Name = "cboFunction";
            this.cboFunction.Size = new System.Drawing.Size(270, 21);
            this.cboFunction.TabIndex = 6;
            // 
            // pnlScene
            // 
            this.pnlScene.Controls.Add(this.cboSceneSelect);
            this.pnlScene.Controls.Add(this.lblScene);
            this.pnlScene.Location = new System.Drawing.Point(12, 156);
            this.pnlScene.Name = "pnlScene";
            this.pnlScene.Size = new System.Drawing.Size(346, 53);
            this.pnlScene.TabIndex = 7;
            this.pnlScene.Visible = false;
            // 
            // cboSceneSelect
            // 
            this.cboSceneSelect.FormattingEnabled = true;
            this.cboSceneSelect.Location = new System.Drawing.Point(54, 12);
            this.cboSceneSelect.Name = "cboSceneSelect";
            this.cboSceneSelect.Size = new System.Drawing.Size(287, 21);
            this.cboSceneSelect.TabIndex = 8;
            // 
            // lblScene
            // 
            this.lblScene.AutoSize = true;
            this.lblScene.Location = new System.Drawing.Point(10, 15);
            this.lblScene.Name = "lblScene";
            this.lblScene.Size = new System.Drawing.Size(38, 13);
            this.lblScene.TabIndex = 0;
            this.lblScene.Text = "Scene";
            // 
            // guiUpdateTimer
            // 
            this.guiUpdateTimer.Interval = 10;
            this.guiUpdateTimer.Tick += new System.EventHandler(this.guiUpdateTimer_Tick);
            // 
            // frmButtonConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(370, 250);
            this.Controls.Add(this.pnlScene);
            this.Controls.Add(this.cboFunction);
            this.Controls.Add(this.lblFunction);
            this.Controls.Add(this.tboColorIndicator);
            this.Controls.Add(this.lblButtonColor);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnAddButton);
            this.Name = "frmButtonConfig";
            this.Text = " ";
            this.Load += new System.EventHandler(this.frmButtonConfig_Load);
            this.pnlScene.ResumeLayout(false);
            this.pnlScene.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAddButton;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.ColorDialog buttonColorDialog;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label lblButtonColor;
        private System.Windows.Forms.TextBox tboColorIndicator;
        private System.Windows.Forms.Label lblFunction;
        private System.Windows.Forms.ComboBox cboFunction;
        private System.Windows.Forms.Panel pnlScene;
        private System.Windows.Forms.ComboBox cboSceneSelect;
        private System.Windows.Forms.Label lblScene;
        private System.Windows.Forms.Timer guiUpdateTimer;
    }
}