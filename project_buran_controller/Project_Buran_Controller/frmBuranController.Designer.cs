
namespace Project_Buran_Controller
{
    partial class frmBuranController
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
            this.olvController = new BrightIdeasSoftware.ObjectListView();
            this.olvBtnName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.olvController)).BeginInit();
            this.SuspendLayout();
            // 
            // olvController
            // 
            this.olvController.AllColumns.Add(this.olvBtnName);
            this.olvController.CellEditUseWholeCell = false;
            this.olvController.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvBtnName});
            this.olvController.Cursor = System.Windows.Forms.Cursors.Default;
            this.olvController.HideSelection = false;
            this.olvController.Location = new System.Drawing.Point(12, 39);
            this.olvController.Name = "olvController";
            this.olvController.Size = new System.Drawing.Size(683, 386);
            this.olvController.TabIndex = 0;
            this.olvController.UseCompatibleStateImageBehavior = false;
            this.olvController.View = System.Windows.Forms.View.Details;
            // 
            // olvBtnName
            // 
            this.olvBtnName.Text = "";
            this.olvBtnName.Width = 91;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(12, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(195, 21);
            this.comboBox1.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(213, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(152, 21);
            this.button1.TabIndex = 2;
            this.button1.Text = "Create Button Profile";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(371, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(159, 21);
            this.button2.TabIndex = 3;
            this.button2.Text = "Apply Profiles";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(536, 12);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(159, 21);
            this.button3.TabIndex = 4;
            this.button3.Text = "Save Profiles";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // frmBuranController
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(711, 437);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.olvController);
            this.Name = "frmBuranController";
            this.Text = "frmBuranController";
            ((System.ComponentModel.ISupportInitialize)(this.olvController)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private BrightIdeasSoftware.ObjectListView olvController;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private BrightIdeasSoftware.OLVColumn olvBtnName;
        private System.Windows.Forms.Button button3;
    }
}

