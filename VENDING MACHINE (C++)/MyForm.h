#pragma once

namespace Project5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			// Set the name to be displayed in the title bar
			this->Text = "My Vending machine";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ comboBox1;
	protected:
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();

			// create arrays to hold the snack items and their prices
			array<String^>^ snackItems = { "Chips ($1.50)", "Candy Bar ($1.00)", "Soda ($2.00)", "Popcorn ($2.00)", "Trail Mix ($2.50)", "Beef Jerky ($3.50)", "Gum ($0.50)", "Cookies ($2.00)", "Pretzels ($1.50)", "Granola Bar ($1.50)", "Nuts ($2.50)", "Crackers ($1.50)", "Chocolates ($2.00)", "Energy Bar ($2.50)" };
			array<double>^ snackPrices = { 1.5, 1.0, 2.0, 2.0, 2.5, 3.5, 0.5, 2.0, 1.5, 1.5, 2.5, 1.5, 2.0, 2.5 };


			// create a drop-down menu for each snack with a label above it
			for (int i = 0; i < snackItems->Length; i++) {
				System::Windows::Forms::Label^ label = (gcnew System::Windows::Forms::Label());
				label->AutoSize = true;
				label->Location = System::Drawing::Point(10 + i * 100, 10);
				label->Name = "label" + (i + 1);
				label->Text = snackItems[i];
				this->Controls->Add(label);

				System::Windows::Forms::ComboBox^ comboBox = (gcnew System::Windows::Forms::ComboBox());
				comboBox->FormattingEnabled = true;
				comboBox->Location = System::Drawing::Point(10 + i * 100, 30);
				comboBox->Name = "comboBox" + (i + 1);
				comboBox->Size = System::Drawing::Size(90, 21);
				comboBox->TabIndex = i;
				comboBox->DropDownStyle = ComboBoxStyle::DropDownList;

				// add the current snack item and its price to the drop-down menu
				comboBox->Items->Add(snackItems[i] + " ($" + snackPrices[i].ToString("F2") + ")");

				// add quantity options to the drop-down menu for the current snack
				array<int>^ quantityOptions = gcnew array<int> { 2, 3, 4, 5 };
				for (int k = 0; k < quantityOptions->Length; k++) {
					comboBox->Items->Add(quantityOptions[k] + " x " + snackItems[i] + " ($" + (snackPrices[i] * quantityOptions[k]).ToString("F2") + ")");
				}

				comboBox->Size = System::Drawing::Size(90, 46);
				this->Controls->Add(comboBox);
			}

			// add a button to the form
			System::Windows::Forms::Button^ button = (gcnew System::Windows::Forms::Button());
			button->Location = System::Drawing::Point(10, 70);
			button->Name = "Bill";
			button->Size = System::Drawing::Size(100, 30);
			button->TabIndex = 6;
			button->Text = "Bill";
			button->UseVisualStyleBackColor = true;
			this->Controls->Add(button);
			button->Click += gcnew System::EventHandler(this, &MyForm::button_Click);

			// 
			// MyForm
			// 
			this->ClientSize = System::Drawing::Size(650, 261);
			this->ImeMode = System::Windows::Forms::ImeMode::KatakanaHalf;
			this->Name = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load_1);
			this->ResumeLayout(false);




		}
	private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e) {

		Cursor->Current = Cursors::WaitCursor;
		Cursor->Current = Cursors::Default;

		double total = 0.0;
		array<String^>^ snackItems = { "Chips ($1.50)", "Candy Bar ($1.00)", "Soda ($2.00)", "Popcorn ($2.00)", "Trail Mix ($2.50)", "Beef Jerky ($3.50)", "Gum ($0.50)", "Cookies ($2.00)", "Pretzels ($1.50)", "Granola Bar ($1.50)", "Nuts ($2.50)", "Crackers ($1.50)", "Chocolates ($2.00)", "Energy Bar ($2.50)" };
		array<double>^ snackPrices = { 1.5, 1.0, 2.0, 2.0, 2.5, 3.5, 0.5, 2.0, 1.5, 1.5, 2.5, 1.5, 2.0, 2.5 };

		for (int i = 0; i < snackItems->Length; i++) {
			ComboBox^ comboBox = dynamic_cast<ComboBox^>(this->Controls["comboBox" + (i + 1)]);
			String^ selected = dynamic_cast<String^>(comboBox->SelectedItem);
			if (selected != nullptr) {
				int quantity = 1;
				int xIndex = selected->IndexOf("x ");
				if (xIndex != -1) {
					String^ quantityString = selected->Substring(0, xIndex);
					if (Int32::TryParse(quantityString, quantity)) {
						selected = selected->Substring(xIndex + 2);
					}
				}
				int openParenIndex = selected->LastIndexOf("(");
				int closeParenIndex = selected->LastIndexOf(")");
				if (openParenIndex != -1 && closeParenIndex != -1 && closeParenIndex > openParenIndex) {
					String^ priceString = selected->Substring(openParenIndex + 2, closeParenIndex - openParenIndex - 2);
					double price = 0.0;
					if (Double::TryParse(priceString, price)) {
						total += price * quantity;
					}
				}
			}
		}
		// Get the user's input amount
		String^ inputAmountString = Microsoft::VisualBasic::Interaction::InputBox("Enter amount:", "Amount", "0");
		int inputAmount;
		if (Int32::TryParse(inputAmountString, inputAmount)) {
			int price = total;
			// Compare the input amount to the product price
			if (inputAmount >= price) {
				double change = inputAmount - total;
				String^ customerNo = "66"; // Change this to the actual customer number
				String^ dateTimeString = DateTime::Now.ToString("MM/dd/yyyy hh:mm tt"); // Get current date/time as string
				String^ message = "Customer No: " + customerNo + "\nDate/Time: " + dateTimeString + "\nTotal: $" + total.ToString("F2") + "\nChange: $" + change.ToString("F2");
				MessageBox::Show(message);
			}
			else {
				MessageBox::Show("Error: Input amount is less than the product price.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else {
			MessageBox::Show("Error: Invalid input amount.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

#pragma endregion

	private:
		System::Void MyForm_Load_1(System::Object^ sender, System::EventArgs^ e) {
		}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
