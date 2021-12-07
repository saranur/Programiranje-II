namespace DateTimeTest
{
    partial class Form1
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
            this.btnDodajDane = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.txtBrojDana = new System.Windows.Forms.TextBox();
            this.lblKonacniDatum = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnDodajDane
            // 
            this.btnDodajDane.Location = new System.Drawing.Point(257, 33);
            this.btnDodajDane.Name = "btnDodajDane";
            this.btnDodajDane.Size = new System.Drawing.Size(102, 28);
            this.btnDodajDane.TabIndex = 0;
            this.btnDodajDane.Text = "Dodaj Dane";
            this.btnDodajDane.UseVisualStyleBackColor = true;
            this.btnDodajDane.Click += new System.EventHandler(this.btnDodajDane_Click);
            // 
            // txtBrojDana
            // 
            this.txtBrojDana.Location = new System.Drawing.Point(48, 36);
            this.txtBrojDana.Name = "txtBrojDana";
            this.txtBrojDana.Size = new System.Drawing.Size(203, 22);
            this.txtBrojDana.TabIndex = 3;
            this.txtBrojDana.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // lblKonacniDatum
            // 
            this.lblKonacniDatum.AutoSize = true;
            this.lblKonacniDatum.Font = new System.Drawing.Font("Microsoft Sans Serif", 30F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblKonacniDatum.Location = new System.Drawing.Point(73, 75);
            this.lblKonacniDatum.Name = "lblKonacniDatum";
            this.lblKonacniDatum.Size = new System.Drawing.Size(0, 58);
            this.lblKonacniDatum.TabIndex = 4;
            this.lblKonacniDatum.Click += new System.EventHandler(this.lblKonacniDatum_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(414, 166);
            this.Controls.Add(this.lblKonacniDatum);
            this.Controls.Add(this.txtBrojDana);
            this.Controls.Add(this.btnDodajDane);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDodajDane;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.TextBox txtBrojDana;
        private System.Windows.Forms.Label lblKonacniDatum;
    }
}

