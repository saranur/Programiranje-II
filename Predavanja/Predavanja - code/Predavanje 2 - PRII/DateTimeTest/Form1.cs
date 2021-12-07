using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DateTimeTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void bindingNavigatorDeleteItem_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void bindingNavigator2_RefreshItems(object sender, EventArgs e)
        {

        }

        private void lblKonacniDatum_Click(object sender, EventArgs e)
        {

        }

        private void btnDodajDane_Click(object sender, EventArgs e)
        {
            try
            {
                //   int brojDana = int.Parse(txtBrojDana.Text);//2 //jer nam ne moze konvertovati string to int, pa koristimo Parse
                //Parse - prevodimo tekst u integer - u momentu kada korisnik unese 1000 npr. to ce biti tekst
                //trenutno se necemo zamarati validacijom (ako korisnik unese slovo, znak...)
                /*
                 DateTime trenutno = DateTime.Now; //16.03.2021
                 DateTime noviDatum= trenutno.AddDays(brojDana); //16.03.2021 + 2

                 //DateTime.Now.AddDays(brojDana);
                 //lblKonacniDatum.Text = noviDatum.ToString("dd.MM.yyyy");
                */
                //zakomentirane linije u jednoj liniji: 
                //  lblKonacniDatum.Text = DateTime.Now.AddDays(brojDana).ToString("dd.MM.yyyy");
                //ili jos: 
                lblKonacniDatum.Text = DateTime.Now.AddDays(int.Parse(txtBrojDana.Text)).ToString("dd.MM.yyyy");
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message); //ukoliko korisnik unese nesto neispravno program nece pasti ali ce samo prikazati upozorenje
            }
        }
    }
}

