#pragma once


#include "ExcelInterface.h"
#include "StimulusControl.h"
#include <sstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace msclr::interop;

namespace BehaviorRig2 {

	/// <summary>
	/// Summary for ExperimentSetUp
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ExperimentSetUp : public System::Windows::Forms::Form
	{
	public:
		ExperimentSetUp(void)
//		ExperimentSetUp(BehaviorRig2::ExperimentParameters^ experimentParameters)
		{
			experimentParameters = gcnew BehaviorRig2::ExperimentParameters;
			experimentParameters->WormTarget = Double(0); // need to initialize "double" values to zero.
			experimentParameters->CantileverFrequency = Double(0);
			experimentParameters->CantileverStiffness = Double(0);
			experimentParameters->CantileverSensitivity = Double(0);


			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ExperimentSetUp()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  closeFormButton;
	protected: 
	private: System::Windows::Forms::Button^  confirmFormButton;
	private: System::Windows::Forms::GroupBox^  clampModeGroupBox;
	private: System::Windows::Forms::RadioButton^  displacementClampRadioButton;
	private: System::Windows::Forms::RadioButton^  forceClampRadioButton;
	private: System::Windows::Forms::GroupBox^  experimentInfoGroupBox;
	private: System::Windows::Forms::Label^  experimentTitleLabel;
	private: System::Windows::Forms::Label^  wormTreatmentsLabel;

	private: System::Windows::Forms::Label^  wormStrainLabel;
	private: System::Windows::Forms::Label^  ambientHumidityLabel;
	private: System::Windows::Forms::Label^  ambientTemperatureLabel;
	private: System::Windows::Forms::Label^  wormGenderLabel;

	private: System::Windows::Forms::Label^  percentAgarLabel;
	private: System::Windows::Forms::Label^  wormAgeLabel;
	private: System::Windows::Forms::TextBox^  ambientTemperatureText;

	private: System::Windows::Forms::TextBox^  ambientHumidityText;

	private: System::Windows::Forms::ComboBox^  wormGenderComboBox;

	private: System::Windows::Forms::TextBox^  percentAgarText;

	private: System::Windows::Forms::TextBox^  wormTreatmentsText;

	private: System::Windows::Forms::TextBox^  wormStrainText;

	private: System::Windows::Forms::TextBox^  experimentTitleText;
	private: System::Windows::Forms::ComboBox^  wormAgeComboBox;


	private: System::Windows::Forms::Label^  otherInfoLabel;
	private: System::Windows::Forms::Label^  ambientTemperatureUnitLabel;

	private: System::Windows::Forms::Label^  ambientHumidityUnitLabel;
	private: System::Windows::Forms::Label^  percentAgarUnitLabel;
	private: System::Windows::Forms::TextBox^  otherInfoText;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::PictureBox^  wormMapPictureBox;
	private: System::Windows::Forms::GroupBox^  targetGroupBox;
	private: System::Windows::Forms::TrackBar^  targetTrackBar;
	private: System::Windows::Forms::Label^  targetValueLabel;
	private: System::Windows::Forms::Label^  targetLabel;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::GroupBox^  dataOutputGroupBox;
	private: System::Windows::Forms::TextBox^  dataOutputFileText;

	private: System::Windows::Forms::Button^  fileBrowseButton;
	private: System::Windows::Forms::GroupBox^  cantileverGroupBox;
	private: System::Windows::Forms::TextBox^  waferIDText;

	private: System::Windows::Forms::Button^  cantileverIDSearchButton;
	private: System::Windows::Forms::Label^  cantileverStiffnessLabel;

	private: System::Windows::Forms::Label^  cantileverFrequencyLabel;
	private: System::Windows::Forms::Label^  cantileverFreqUnitLabel;
	private: System::Windows::Forms::TextBox^  cantileverStiffnessText;
	private: System::Windows::Forms::TextBox^  cantileverFrequencyText;
	private: System::Windows::Forms::Label^  cantileverStiffnessUnitLabel;
	private: System::Windows::Forms::Label^  cantileverSensitivityLabel;
	private: System::Windows::Forms::TextBox^  cantileverSensitivityText;
	private: System::Windows::Forms::Label^  cantileverIDInstructionsLabel;

	private: System::Windows::Forms::Label^  cantileverSensitivityUnitLabel;
	private: System::Windows::Forms::Label^  cantileverSpecLabel;
	private: System::Windows::Forms::TextBox^  deviceIDText;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::GroupBox^  stimulusGroupBox;
private: System::Windows::Forms::GroupBox^  stimTypeGroupBox;
private: System::Windows::Forms::RadioButton^  customStimRadioButton;


private: System::Windows::Forms::RadioButton^  sineStimRadioButton;
private: System::Windows::Forms::RadioButton^  triangleStimRadioButton;
private: System::Windows::Forms::RadioButton^  squareStimRadioButton;
private: System::Windows::Forms::Button^  findCustomStimButton;
private: System::Windows::Forms::TextBox^  customStimFileText;


private: System::Windows::Forms::TextBox^  magnitudeStimText;

private: System::Windows::Forms::TextBox^  noCyclesStimText;

private: System::Windows::Forms::TextBox^  dutyCycleStimText;

private: System::Windows::Forms::TextBox^  frequencyStimText;

private: System::Windows::Forms::Button^  showStimulusButton;
private: System::Windows::Forms::Label^  magnitudeStimLabel;

private: System::Windows::Forms::Label^  noCyclesStimLabel;
private: System::Windows::Forms::Label^  customStimFileLabel;


private: System::Windows::Forms::Label^  dutyCycleStimLabel;

private: System::Windows::Forms::Label^  frequencyStimLabel;
private: System::Windows::Forms::ComboBox^  scaleTypeStimComboBox;


private: System::Windows::Forms::TextBox^  scaleStimText;

private: System::Windows::Forms::Label^  scaleTypeStimLabel;

private: System::Windows::Forms::Label^  scaleStimLabel;
private: System::Windows::Forms::Label^  magnitudeStimUnitLabel;


private: System::Windows::Forms::Label^  noCyclesStimUnitLabel;

private: System::Windows::Forms::Label^  dutyCycleStimUnitLabel;

private: System::Windows::Forms::Label^  frequencyStimUnitLabel;
private: System::Windows::Forms::OpenFileDialog^  customStimOpenFileDialog;
private: System::Windows::Forms::TextBox^  sineStimFrequencyText;

private: System::Windows::Forms::TextBox^  sineStimBiasText;
private: System::Windows::Forms::Label^  sineStimBiasUnitLabel;

private: System::Windows::Forms::Label^  sineStimFrequencyUnitLabel;
private: System::Windows::Forms::Label^  sineStimBiasLabel;
private: System::Windows::Forms::Label^  sineStimFrequencyLabel;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  stimulusSignalPlot;


















	BehaviorRig2::ExperimentParameters^ experimentParameters;

	public:
		property BehaviorRig2::ExperimentParameters^ ExperimentParameters
		{
			BehaviorRig2::ExperimentParameters^ get()
			{
				return this-> experimentParameters;
			}
		}



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ExperimentSetUp::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->closeFormButton = (gcnew System::Windows::Forms::Button());
			this->confirmFormButton = (gcnew System::Windows::Forms::Button());
			this->clampModeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->displacementClampRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->forceClampRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->experimentInfoGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->ambientTemperatureUnitLabel = (gcnew System::Windows::Forms::Label());
			this->ambientHumidityUnitLabel = (gcnew System::Windows::Forms::Label());
			this->percentAgarUnitLabel = (gcnew System::Windows::Forms::Label());
			this->otherInfoText = (gcnew System::Windows::Forms::TextBox());
			this->ambientTemperatureText = (gcnew System::Windows::Forms::TextBox());
			this->ambientHumidityText = (gcnew System::Windows::Forms::TextBox());
			this->wormGenderComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->percentAgarText = (gcnew System::Windows::Forms::TextBox());
			this->wormTreatmentsText = (gcnew System::Windows::Forms::TextBox());
			this->wormStrainText = (gcnew System::Windows::Forms::TextBox());
			this->experimentTitleText = (gcnew System::Windows::Forms::TextBox());
			this->wormAgeComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->otherInfoLabel = (gcnew System::Windows::Forms::Label());
			this->wormAgeLabel = (gcnew System::Windows::Forms::Label());
			this->wormGenderLabel = (gcnew System::Windows::Forms::Label());
			this->percentAgarLabel = (gcnew System::Windows::Forms::Label());
			this->ambientTemperatureLabel = (gcnew System::Windows::Forms::Label());
			this->ambientHumidityLabel = (gcnew System::Windows::Forms::Label());
			this->wormTreatmentsLabel = (gcnew System::Windows::Forms::Label());
			this->wormStrainLabel = (gcnew System::Windows::Forms::Label());
			this->experimentTitleLabel = (gcnew System::Windows::Forms::Label());
			this->wormMapPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->targetGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->targetValueLabel = (gcnew System::Windows::Forms::Label());
			this->targetLabel = (gcnew System::Windows::Forms::Label());
			this->targetTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->dataOutputGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->dataOutputFileText = (gcnew System::Windows::Forms::TextBox());
			this->fileBrowseButton = (gcnew System::Windows::Forms::Button());
			this->cantileverGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->deviceIDText = (gcnew System::Windows::Forms::TextBox());
			this->cantileverSpecLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverIDInstructionsLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverSensitivityUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverSensitivityText = (gcnew System::Windows::Forms::TextBox());
			this->cantileverSensitivityLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverStiffnessUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverFreqUnitLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverStiffnessText = (gcnew System::Windows::Forms::TextBox());
			this->cantileverFrequencyText = (gcnew System::Windows::Forms::TextBox());
			this->cantileverStiffnessLabel = (gcnew System::Windows::Forms::Label());
			this->cantileverFrequencyLabel = (gcnew System::Windows::Forms::Label());
			this->waferIDText = (gcnew System::Windows::Forms::TextBox());
			this->cantileverIDSearchButton = (gcnew System::Windows::Forms::Button());
			this->stimulusGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stimulusSignalPlot = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->sineStimBiasUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineStimFrequencyUnitLabel = (gcnew System::Windows::Forms::Label());
			this->sineStimBiasLabel = (gcnew System::Windows::Forms::Label());
			this->sineStimFrequencyLabel = (gcnew System::Windows::Forms::Label());
			this->sineStimBiasText = (gcnew System::Windows::Forms::TextBox());
			this->sineStimFrequencyText = (gcnew System::Windows::Forms::TextBox());
			this->magnitudeStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->noCyclesStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->dutyCycleStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->frequencyStimUnitLabel = (gcnew System::Windows::Forms::Label());
			this->scaleTypeStimLabel = (gcnew System::Windows::Forms::Label());
			this->scaleStimLabel = (gcnew System::Windows::Forms::Label());
			this->scaleStimText = (gcnew System::Windows::Forms::TextBox());
			this->scaleTypeStimComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->magnitudeStimLabel = (gcnew System::Windows::Forms::Label());
			this->noCyclesStimLabel = (gcnew System::Windows::Forms::Label());
			this->customStimFileLabel = (gcnew System::Windows::Forms::Label());
			this->dutyCycleStimLabel = (gcnew System::Windows::Forms::Label());
			this->frequencyStimLabel = (gcnew System::Windows::Forms::Label());
			this->findCustomStimButton = (gcnew System::Windows::Forms::Button());
			this->customStimFileText = (gcnew System::Windows::Forms::TextBox());
			this->magnitudeStimText = (gcnew System::Windows::Forms::TextBox());
			this->noCyclesStimText = (gcnew System::Windows::Forms::TextBox());
			this->dutyCycleStimText = (gcnew System::Windows::Forms::TextBox());
			this->frequencyStimText = (gcnew System::Windows::Forms::TextBox());
			this->showStimulusButton = (gcnew System::Windows::Forms::Button());
			this->stimTypeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->customStimRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->sineStimRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->triangleStimRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->squareStimRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->customStimOpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->clampModeGroupBox->SuspendLayout();
			this->experimentInfoGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->wormMapPictureBox))->BeginInit();
			this->targetGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetTrackBar))->BeginInit();
			this->dataOutputGroupBox->SuspendLayout();
			this->cantileverGroupBox->SuspendLayout();
			this->stimulusGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalPlot))->BeginInit();
			this->stimTypeGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// closeFormButton
			// 
			this->closeFormButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->closeFormButton->Location = System::Drawing::Point(719, 604);
			this->closeFormButton->Name = L"closeFormButton";
			this->closeFormButton->Size = System::Drawing::Size(75, 23);
			this->closeFormButton->TabIndex = 0;
			this->closeFormButton->Text = L"Cancel";
			this->closeFormButton->UseVisualStyleBackColor = true;
			// 
			// confirmFormButton
			// 
			this->confirmFormButton->Location = System::Drawing::Point(634, 604);
			this->confirmFormButton->Name = L"confirmFormButton";
			this->confirmFormButton->Size = System::Drawing::Size(75, 23);
			this->confirmFormButton->TabIndex = 1;
			this->confirmFormButton->Text = L"OK";
			this->confirmFormButton->UseVisualStyleBackColor = true;
			this->confirmFormButton->Click += gcnew System::EventHandler(this, &ExperimentSetUp::confirmFormButton_Click);
			// 
			// clampModeGroupBox
			// 
			this->clampModeGroupBox->Controls->Add(this->displacementClampRadioButton);
			this->clampModeGroupBox->Controls->Add(this->forceClampRadioButton);
			this->clampModeGroupBox->Location = System::Drawing::Point(334, 12);
			this->clampModeGroupBox->Name = L"clampModeGroupBox";
			this->clampModeGroupBox->Size = System::Drawing::Size(133, 72);
			this->clampModeGroupBox->TabIndex = 2;
			this->clampModeGroupBox->TabStop = false;
			this->clampModeGroupBox->Text = L"Clamp Mode";
			// 
			// displacementClampRadioButton
			// 
			this->displacementClampRadioButton->AutoSize = true;
			this->displacementClampRadioButton->Location = System::Drawing::Point(7, 43);
			this->displacementClampRadioButton->Name = L"displacementClampRadioButton";
			this->displacementClampRadioButton->Size = System::Drawing::Size(121, 17);
			this->displacementClampRadioButton->TabIndex = 11;
			this->displacementClampRadioButton->TabStop = true;
			this->displacementClampRadioButton->Text = L"Displacement Clamp";
			this->displacementClampRadioButton->UseVisualStyleBackColor = true;
			this->displacementClampRadioButton->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::displacementClampRadioButton_Validated);
			// 
			// forceClampRadioButton
			// 
			this->forceClampRadioButton->AutoSize = true;
			this->forceClampRadioButton->Location = System::Drawing::Point(7, 20);
			this->forceClampRadioButton->Name = L"forceClampRadioButton";
			this->forceClampRadioButton->Size = System::Drawing::Size(84, 17);
			this->forceClampRadioButton->TabIndex = 10;
			this->forceClampRadioButton->TabStop = true;
			this->forceClampRadioButton->Text = L"Force Clamp";
			this->forceClampRadioButton->UseVisualStyleBackColor = true;
			this->forceClampRadioButton->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::forceClampRadioButton_Validated);
			// 
			// experimentInfoGroupBox
			// 
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarUnitLabel);
			this->experimentInfoGroupBox->Controls->Add(this->otherInfoText);
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureText);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityText);
			this->experimentInfoGroupBox->Controls->Add(this->wormGenderComboBox);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarText);
			this->experimentInfoGroupBox->Controls->Add(this->wormTreatmentsText);
			this->experimentInfoGroupBox->Controls->Add(this->wormStrainText);
			this->experimentInfoGroupBox->Controls->Add(this->experimentTitleText);
			this->experimentInfoGroupBox->Controls->Add(this->wormAgeComboBox);
			this->experimentInfoGroupBox->Controls->Add(this->otherInfoLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormAgeLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormGenderLabel);
			this->experimentInfoGroupBox->Controls->Add(this->percentAgarLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientTemperatureLabel);
			this->experimentInfoGroupBox->Controls->Add(this->ambientHumidityLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormTreatmentsLabel);
			this->experimentInfoGroupBox->Controls->Add(this->wormStrainLabel);
			this->experimentInfoGroupBox->Controls->Add(this->experimentTitleLabel);
			this->experimentInfoGroupBox->Location = System::Drawing::Point(12, 12);
			this->experimentInfoGroupBox->Name = L"experimentInfoGroupBox";
			this->experimentInfoGroupBox->Size = System::Drawing::Size(316, 309);
			this->experimentInfoGroupBox->TabIndex = 3;
			this->experimentInfoGroupBox->TabStop = false;
			this->experimentInfoGroupBox->Text = L"Experiment Information";
			// 
			// ambientTemperatureUnitLabel
			// 
			this->ambientTemperatureUnitLabel->AutoSize = true;
			this->ambientTemperatureUnitLabel->Location = System::Drawing::Point(174, 179);
			this->ambientTemperatureUnitLabel->Name = L"ambientTemperatureUnitLabel";
			this->ambientTemperatureUnitLabel->Size = System::Drawing::Size(55, 13);
			this->ambientTemperatureUnitLabel->TabIndex = 20;
			this->ambientTemperatureUnitLabel->Text = L"degrees C";
			// 
			// ambientHumidityUnitLabel
			// 
			this->ambientHumidityUnitLabel->AutoSize = true;
			this->ambientHumidityUnitLabel->Location = System::Drawing::Point(174, 158);
			this->ambientHumidityUnitLabel->Name = L"ambientHumidityUnitLabel";
			this->ambientHumidityUnitLabel->Size = System::Drawing::Size(15, 13);
			this->ambientHumidityUnitLabel->TabIndex = 19;
			this->ambientHumidityUnitLabel->Text = L"%";
			// 
			// percentAgarUnitLabel
			// 
			this->percentAgarUnitLabel->AutoSize = true;
			this->percentAgarUnitLabel->Location = System::Drawing::Point(187, 88);
			this->percentAgarUnitLabel->Name = L"percentAgarUnitLabel";
			this->percentAgarUnitLabel->Size = System::Drawing::Size(15, 13);
			this->percentAgarUnitLabel->TabIndex = 18;
			this->percentAgarUnitLabel->Text = L"%";
			// 
			// otherInfoText
			// 
			this->otherInfoText->Location = System::Drawing::Point(141, 197);
			this->otherInfoText->Multiline = true;
			this->otherInfoText->Name = L"otherInfoText";
			this->otherInfoText->Size = System::Drawing::Size(169, 107);
			this->otherInfoText->TabIndex = 9;
			this->otherInfoText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::otherInfoText_Validated);
			// 
			// ambientTemperatureText
			// 
			this->ambientTemperatureText->Location = System::Drawing::Point(141, 176);
			this->ambientTemperatureText->Name = L"ambientTemperatureText";
			this->ambientTemperatureText->Size = System::Drawing::Size(33, 20);
			this->ambientTemperatureText->TabIndex = 8;
			this->ambientTemperatureText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::ambientTemperatureText_Validated);
			// 
			// ambientHumidityText
			// 
			this->ambientHumidityText->Location = System::Drawing::Point(141, 154);
			this->ambientHumidityText->Name = L"ambientHumidityText";
			this->ambientHumidityText->Size = System::Drawing::Size(33, 20);
			this->ambientHumidityText->TabIndex = 7;
			this->ambientHumidityText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::ambientHumidityText_Validated);
			// 
			// wormGenderComboBox
			// 
			this->wormGenderComboBox->FormattingEnabled = true;
			this->wormGenderComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Male", L"Hermaphradite"});
			this->wormGenderComboBox->Location = System::Drawing::Point(141, 107);
			this->wormGenderComboBox->Name = L"wormGenderComboBox";
			this->wormGenderComboBox->Size = System::Drawing::Size(155, 21);
			this->wormGenderComboBox->TabIndex = 5;
			this->wormGenderComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ExperimentSetUp::wormGenderComboBox_SelectedIndexChanged);
			// 
			// percentAgarText
			// 
			this->percentAgarText->Location = System::Drawing::Point(141, 85);
			this->percentAgarText->Name = L"percentAgarText";
			this->percentAgarText->Size = System::Drawing::Size(45, 20);
			this->percentAgarText->TabIndex = 4;
			this->percentAgarText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::percentAgarText_Validated);
			// 
			// wormTreatmentsText
			// 
			this->wormTreatmentsText->Location = System::Drawing::Point(141, 63);
			this->wormTreatmentsText->Name = L"wormTreatmentsText";
			this->wormTreatmentsText->Size = System::Drawing::Size(169, 20);
			this->wormTreatmentsText->TabIndex = 3;
			this->wormTreatmentsText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::wormTreatmentsText_Validated);
			// 
			// wormStrainText
			// 
			this->wormStrainText->Location = System::Drawing::Point(141, 41);
			this->wormStrainText->Name = L"wormStrainText";
			this->wormStrainText->Size = System::Drawing::Size(169, 20);
			this->wormStrainText->TabIndex = 2;
			this->wormStrainText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::wormStrainText_Validated);
			// 
			// experimentTitleText
			// 
			this->experimentTitleText->Location = System::Drawing::Point(141, 20);
			this->experimentTitleText->Name = L"experimentTitleText";
			this->experimentTitleText->Size = System::Drawing::Size(169, 20);
			this->experimentTitleText->TabIndex = 1;
			this->experimentTitleText->Validated += gcnew System::EventHandler(this, &ExperimentSetUp::experimentTitleText_Validated);
			// 
			// wormAgeComboBox
			// 
			this->wormAgeComboBox->FormattingEnabled = true;
			this->wormAgeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"L1", L"L2", L"L3", L"L4", L"Adult"});
			this->wormAgeComboBox->Location = System::Drawing::Point(141, 129);
			this->wormAgeComboBox->Name = L"wormAgeComboBox";
			this->wormAgeComboBox->Size = System::Drawing::Size(79, 21);
			this->wormAgeComboBox->TabIndex = 6;
			this->wormAgeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ExperimentSetUp::wormAgeComboBox_SelectedIndexChanged);
			// 
			// otherInfoLabel
			// 
			this->otherInfoLabel->AutoSize = true;
			this->otherInfoLabel->Location = System::Drawing::Point(6, 200);
			this->otherInfoLabel->Name = L"otherInfoLabel";
			this->otherInfoLabel->Size = System::Drawing::Size(122, 13);
			this->otherInfoLabel->TabIndex = 8;
			this->otherInfoLabel->Text = L"Other Experiment Notes:";
			// 
			// wormAgeLabel
			// 
			this->wormAgeLabel->AutoSize = true;
			this->wormAgeLabel->Location = System::Drawing::Point(7, 129);
			this->wormAgeLabel->Name = L"wormAgeLabel";
			this->wormAgeLabel->Size = System::Drawing::Size(60, 13);
			this->wormAgeLabel->TabIndex = 7;
			this->wormAgeLabel->Text = L"Worm Age:";
			// 
			// wormGenderLabel
			// 
			this->wormGenderLabel->AutoSize = true;
			this->wormGenderLabel->Location = System::Drawing::Point(6, 107);
			this->wormGenderLabel->Name = L"wormGenderLabel";
			this->wormGenderLabel->Size = System::Drawing::Size(76, 13);
			this->wormGenderLabel->TabIndex = 6;
			this->wormGenderLabel->Text = L"Worm Gender:";
			// 
			// percentAgarLabel
			// 
			this->percentAgarLabel->AutoSize = true;
			this->percentAgarLabel->Location = System::Drawing::Point(7, 85);
			this->percentAgarLabel->Name = L"percentAgarLabel";
			this->percentAgarLabel->Size = System::Drawing::Size(43, 13);
			this->percentAgarLabel->TabIndex = 5;
			this->percentAgarLabel->Text = L"% Agar:";
			// 
			// ambientTemperatureLabel
			// 
			this->ambientTemperatureLabel->AutoSize = true;
			this->ambientTemperatureLabel->Location = System::Drawing::Point(7, 176);
			this->ambientTemperatureLabel->Name = L"ambientTemperatureLabel";
			this->ambientTemperatureLabel->Size = System::Drawing::Size(111, 13);
			this->ambientTemperatureLabel->TabIndex = 4;
			this->ambientTemperatureLabel->Text = L"Ambient Temperature:";
			// 
			// ambientHumidityLabel
			// 
			this->ambientHumidityLabel->AutoSize = true;
			this->ambientHumidityLabel->Location = System::Drawing::Point(7, 154);
			this->ambientHumidityLabel->Name = L"ambientHumidityLabel";
			this->ambientHumidityLabel->Size = System::Drawing::Size(91, 13);
			this->ambientHumidityLabel->TabIndex = 3;
			this->ambientHumidityLabel->Text = L"Ambient Humidity:";
			// 
			// wormTreatmentsLabel
			// 
			this->wormTreatmentsLabel->AutoSize = true;
			this->wormTreatmentsLabel->Location = System::Drawing::Point(7, 63);
			this->wormTreatmentsLabel->Name = L"wormTreatmentsLabel";
			this->wormTreatmentsLabel->Size = System::Drawing::Size(94, 13);
			this->wormTreatmentsLabel->TabIndex = 2;
			this->wormTreatmentsLabel->Text = L"Worm Treatments:";
			// 
			// wormStrainLabel
			// 
			this->wormStrainLabel->AutoSize = true;
			this->wormStrainLabel->Location = System::Drawing::Point(7, 41);
			this->wormStrainLabel->Name = L"wormStrainLabel";
			this->wormStrainLabel->Size = System::Drawing::Size(71, 13);
			this->wormStrainLabel->TabIndex = 1;
			this->wormStrainLabel->Text = L"Worm Strain: ";
			// 
			// experimentTitleLabel
			// 
			this->experimentTitleLabel->AutoSize = true;
			this->experimentTitleLabel->Location = System::Drawing::Point(7, 20);
			this->experimentTitleLabel->Name = L"experimentTitleLabel";
			this->experimentTitleLabel->Size = System::Drawing::Size(85, 13);
			this->experimentTitleLabel->TabIndex = 0;
			this->experimentTitleLabel->Text = L"Experiment Title:";
			// 
			// wormMapPictureBox
			// 
			this->wormMapPictureBox->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"wormMapPictureBox.Image")));
			this->wormMapPictureBox->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"wormMapPictureBox.InitialImage")));
			this->wormMapPictureBox->Location = System::Drawing::Point(18, 91);
			this->wormMapPictureBox->Name = L"wormMapPictureBox";
			this->wormMapPictureBox->Size = System::Drawing::Size(430, 86);
			this->wormMapPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->wormMapPictureBox->TabIndex = 4;
			this->wormMapPictureBox->TabStop = false;
			// 
			// targetGroupBox
			// 
			this->targetGroupBox->Controls->Add(this->targetValueLabel);
			this->targetGroupBox->Controls->Add(this->targetLabel);
			this->targetGroupBox->Controls->Add(this->targetTrackBar);
			this->targetGroupBox->Controls->Add(this->wormMapPictureBox);
			this->targetGroupBox->Location = System::Drawing::Point(334, 90);
			this->targetGroupBox->Name = L"targetGroupBox";
			this->targetGroupBox->Size = System::Drawing::Size(461, 183);
			this->targetGroupBox->TabIndex = 5;
			this->targetGroupBox->TabStop = false;
			this->targetGroupBox->Text = L"Target Selection";
			// 
			// targetValueLabel
			// 
			this->targetValueLabel->AutoSize = true;
			this->targetValueLabel->Location = System::Drawing::Point(62, 20);
			this->targetValueLabel->Name = L"targetValueLabel";
			this->targetValueLabel->Size = System::Drawing::Size(0, 13);
			this->targetValueLabel->TabIndex = 7;
			// 
			// targetLabel
			// 
			this->targetLabel->AutoSize = true;
			this->targetLabel->Location = System::Drawing::Point(18, 20);
			this->targetLabel->Name = L"targetLabel";
			this->targetLabel->Size = System::Drawing::Size(44, 13);
			this->targetLabel->TabIndex = 6;
			this->targetLabel->Text = L"Target: ";
			// 
			// targetTrackBar
			// 
			this->targetTrackBar->Location = System::Drawing::Point(12, 48);
			this->targetTrackBar->Maximum = 100;
			this->targetTrackBar->Name = L"targetTrackBar";
			this->targetTrackBar->Size = System::Drawing::Size(437, 45);
			this->targetTrackBar->TabIndex = 5;
			this->targetTrackBar->TickFrequency = 10;
			this->targetTrackBar->Scroll += gcnew System::EventHandler(this, &ExperimentSetUp::targetTrackBar_Scroll);
			// 
			// folderBrowserDialog
			// 
			this->folderBrowserDialog->HelpRequest += gcnew System::EventHandler(this, &ExperimentSetUp::folderBrowserDialog_HelpRequest);
			// 
			// dataOutputGroupBox
			// 
			this->dataOutputGroupBox->Controls->Add(this->dataOutputFileText);
			this->dataOutputGroupBox->Controls->Add(this->fileBrowseButton);
			this->dataOutputGroupBox->Location = System::Drawing::Point(474, 12);
			this->dataOutputGroupBox->Name = L"dataOutputGroupBox";
			this->dataOutputGroupBox->Size = System::Drawing::Size(321, 72);
			this->dataOutputGroupBox->TabIndex = 6;
			this->dataOutputGroupBox->TabStop = false;
			this->dataOutputGroupBox->Text = L"Data Output Location";
			// 
			// dataOutputFileText
			// 
			this->dataOutputFileText->Location = System::Drawing::Point(7, 33);
			this->dataOutputFileText->Name = L"dataOutputFileText";
			this->dataOutputFileText->Size = System::Drawing::Size(219, 20);
			this->dataOutputFileText->TabIndex = 1;
			// 
			// fileBrowseButton
			// 
			this->fileBrowseButton->Location = System::Drawing::Point(232, 30);
			this->fileBrowseButton->Name = L"fileBrowseButton";
			this->fileBrowseButton->Size = System::Drawing::Size(75, 23);
			this->fileBrowseButton->TabIndex = 0;
			this->fileBrowseButton->Text = L"Browse";
			this->fileBrowseButton->UseVisualStyleBackColor = true;
			this->fileBrowseButton->Click += gcnew System::EventHandler(this, &ExperimentSetUp::fileBrowseButton_Click);
			// 
			// cantileverGroupBox
			// 
			this->cantileverGroupBox->Controls->Add(this->label1);
			this->cantileverGroupBox->Controls->Add(this->deviceIDText);
			this->cantileverGroupBox->Controls->Add(this->cantileverSpecLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverIDInstructionsLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityText);
			this->cantileverGroupBox->Controls->Add(this->cantileverSensitivityLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverFreqUnitLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessText);
			this->cantileverGroupBox->Controls->Add(this->cantileverFrequencyText);
			this->cantileverGroupBox->Controls->Add(this->cantileverStiffnessLabel);
			this->cantileverGroupBox->Controls->Add(this->cantileverFrequencyLabel);
			this->cantileverGroupBox->Controls->Add(this->waferIDText);
			this->cantileverGroupBox->Controls->Add(this->cantileverIDSearchButton);
			this->cantileverGroupBox->Location = System::Drawing::Point(12, 328);
			this->cantileverGroupBox->Name = L"cantileverGroupBox";
			this->cantileverGroupBox->Size = System::Drawing::Size(316, 268);
			this->cantileverGroupBox->TabIndex = 7;
			this->cantileverGroupBox->TabStop = false;
			this->cantileverGroupBox->Text = L"Cantilever";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 62);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(265, 13);
			this->label1->TabIndex = 14;
			this->label1->Text = L"Enter device coordinate code (####), press \"Search\":";
			// 
			// deviceIDText
			// 
			this->deviceIDText->Location = System::Drawing::Point(14, 81);
			this->deviceIDText->Name = L"deviceIDText";
			this->deviceIDText->Size = System::Drawing::Size(100, 20);
			this->deviceIDText->TabIndex = 13;
			// 
			// cantileverSpecLabel
			// 
			this->cantileverSpecLabel->AutoSize = true;
			this->cantileverSpecLabel->Location = System::Drawing::Point(15, 117);
			this->cantileverSpecLabel->Name = L"cantileverSpecLabel";
			this->cantileverSpecLabel->Size = System::Drawing::Size(126, 13);
			this->cantileverSpecLabel->TabIndex = 12;
			this->cantileverSpecLabel->Text = L"Cantliever Specifications:";
			// 
			// cantileverIDInstructionsLabel
			// 
			this->cantileverIDInstructionsLabel->AutoSize = true;
			this->cantileverIDInstructionsLabel->Location = System::Drawing::Point(14, 19);
			this->cantileverIDInstructionsLabel->Name = L"cantileverIDInstructionsLabel";
			this->cantileverIDInstructionsLabel->Size = System::Drawing::Size(163, 13);
			this->cantileverIDInstructionsLabel->TabIndex = 11;
			this->cantileverIDInstructionsLabel->Text = L"Enter Wafer ID number (AA##A):";
			// 
			// cantileverSensitivityUnitLabel
			// 
			this->cantileverSensitivityUnitLabel->AutoSize = true;
			this->cantileverSensitivityUnitLabel->Location = System::Drawing::Point(182, 191);
			this->cantileverSensitivityUnitLabel->Name = L"cantileverSensitivityUnitLabel";
			this->cantileverSensitivityUnitLabel->Size = System::Drawing::Size(27, 13);
			this->cantileverSensitivityUnitLabel->TabIndex = 10;
			this->cantileverSensitivityUnitLabel->Text = L"V/N";
			// 
			// cantileverSensitivityText
			// 
			this->cantileverSensitivityText->Location = System::Drawing::Point(80, 187);
			this->cantileverSensitivityText->Name = L"cantileverSensitivityText";
			this->cantileverSensitivityText->Size = System::Drawing::Size(100, 20);
			this->cantileverSensitivityText->TabIndex = 9;
			// 
			// cantileverSensitivityLabel
			// 
			this->cantileverSensitivityLabel->AutoSize = true;
			this->cantileverSensitivityLabel->Location = System::Drawing::Point(14, 190);
			this->cantileverSensitivityLabel->Name = L"cantileverSensitivityLabel";
			this->cantileverSensitivityLabel->Size = System::Drawing::Size(57, 13);
			this->cantileverSensitivityLabel->TabIndex = 8;
			this->cantileverSensitivityLabel->Text = L"Sensitivity:";
			// 
			// cantileverStiffnessUnitLabel
			// 
			this->cantileverStiffnessUnitLabel->AutoSize = true;
			this->cantileverStiffnessUnitLabel->Location = System::Drawing::Point(181, 166);
			this->cantileverStiffnessUnitLabel->Name = L"cantileverStiffnessUnitLabel";
			this->cantileverStiffnessUnitLabel->Size = System::Drawing::Size(28, 13);
			this->cantileverStiffnessUnitLabel->TabIndex = 7;
			this->cantileverStiffnessUnitLabel->Text = L"N/m";
			// 
			// cantileverFreqUnitLabel
			// 
			this->cantileverFreqUnitLabel->AutoSize = true;
			this->cantileverFreqUnitLabel->Location = System::Drawing::Point(181, 141);
			this->cantileverFreqUnitLabel->Name = L"cantileverFreqUnitLabel";
			this->cantileverFreqUnitLabel->Size = System::Drawing::Size(20, 13);
			this->cantileverFreqUnitLabel->TabIndex = 6;
			this->cantileverFreqUnitLabel->Text = L"Hz";
			// 
			// cantileverStiffnessText
			// 
			this->cantileverStiffnessText->Location = System::Drawing::Point(80, 161);
			this->cantileverStiffnessText->Name = L"cantileverStiffnessText";
			this->cantileverStiffnessText->Size = System::Drawing::Size(100, 20);
			this->cantileverStiffnessText->TabIndex = 5;
			// 
			// cantileverFrequencyText
			// 
			this->cantileverFrequencyText->Location = System::Drawing::Point(80, 136);
			this->cantileverFrequencyText->Name = L"cantileverFrequencyText";
			this->cantileverFrequencyText->Size = System::Drawing::Size(100, 20);
			this->cantileverFrequencyText->TabIndex = 4;
			// 
			// cantileverStiffnessLabel
			// 
			this->cantileverStiffnessLabel->AutoSize = true;
			this->cantileverStiffnessLabel->Location = System::Drawing::Point(14, 165);
			this->cantileverStiffnessLabel->Name = L"cantileverStiffnessLabel";
			this->cantileverStiffnessLabel->Size = System::Drawing::Size(50, 13);
			this->cantileverStiffnessLabel->TabIndex = 3;
			this->cantileverStiffnessLabel->Text = L"Stiffness:";
			// 
			// cantileverFrequencyLabel
			// 
			this->cantileverFrequencyLabel->AutoSize = true;
			this->cantileverFrequencyLabel->Location = System::Drawing::Point(14, 139);
			this->cantileverFrequencyLabel->Name = L"cantileverFrequencyLabel";
			this->cantileverFrequencyLabel->Size = System::Drawing::Size(60, 13);
			this->cantileverFrequencyLabel->TabIndex = 2;
			this->cantileverFrequencyLabel->Text = L"Frequency:";
			// 
			// waferIDText
			// 
			this->waferIDText->Location = System::Drawing::Point(14, 39);
			this->waferIDText->Name = L"waferIDText";
			this->waferIDText->Size = System::Drawing::Size(100, 20);
			this->waferIDText->TabIndex = 1;
			// 
			// cantileverIDSearchButton
			// 
			this->cantileverIDSearchButton->Location = System::Drawing::Point(120, 79);
			this->cantileverIDSearchButton->Name = L"cantileverIDSearchButton";
			this->cantileverIDSearchButton->Size = System::Drawing::Size(75, 23);
			this->cantileverIDSearchButton->TabIndex = 0;
			this->cantileverIDSearchButton->Text = L"Search";
			this->cantileverIDSearchButton->UseVisualStyleBackColor = true;
			this->cantileverIDSearchButton->Click += gcnew System::EventHandler(this, &ExperimentSetUp::cantileverIDSearchButton_Click);
			// 
			// stimulusGroupBox
			// 
			this->stimulusGroupBox->Controls->Add(this->stimulusSignalPlot);
			this->stimulusGroupBox->Controls->Add(this->sineStimBiasUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->sineStimFrequencyUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->sineStimBiasLabel);
			this->stimulusGroupBox->Controls->Add(this->sineStimFrequencyLabel);
			this->stimulusGroupBox->Controls->Add(this->sineStimBiasText);
			this->stimulusGroupBox->Controls->Add(this->sineStimFrequencyText);
			this->stimulusGroupBox->Controls->Add(this->magnitudeStimUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->noCyclesStimUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->dutyCycleStimUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->frequencyStimUnitLabel);
			this->stimulusGroupBox->Controls->Add(this->scaleTypeStimLabel);
			this->stimulusGroupBox->Controls->Add(this->scaleStimLabel);
			this->stimulusGroupBox->Controls->Add(this->scaleStimText);
			this->stimulusGroupBox->Controls->Add(this->scaleTypeStimComboBox);
			this->stimulusGroupBox->Controls->Add(this->magnitudeStimLabel);
			this->stimulusGroupBox->Controls->Add(this->noCyclesStimLabel);
			this->stimulusGroupBox->Controls->Add(this->customStimFileLabel);
			this->stimulusGroupBox->Controls->Add(this->dutyCycleStimLabel);
			this->stimulusGroupBox->Controls->Add(this->frequencyStimLabel);
			this->stimulusGroupBox->Controls->Add(this->findCustomStimButton);
			this->stimulusGroupBox->Controls->Add(this->customStimFileText);
			this->stimulusGroupBox->Controls->Add(this->magnitudeStimText);
			this->stimulusGroupBox->Controls->Add(this->noCyclesStimText);
			this->stimulusGroupBox->Controls->Add(this->dutyCycleStimText);
			this->stimulusGroupBox->Controls->Add(this->frequencyStimText);
			this->stimulusGroupBox->Controls->Add(this->showStimulusButton);
			this->stimulusGroupBox->Controls->Add(this->stimTypeGroupBox);
			this->stimulusGroupBox->Location = System::Drawing::Point(334, 280);
			this->stimulusGroupBox->Name = L"stimulusGroupBox";
			this->stimulusGroupBox->Size = System::Drawing::Size(461, 316);
			this->stimulusGroupBox->TabIndex = 8;
			this->stimulusGroupBox->TabStop = false;
			this->stimulusGroupBox->Text = L"Stimulus";
			// 
			// stimulusSignalPlot
			// 
			chartArea1->Name = L"ChartArea1";
			this->stimulusSignalPlot->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->stimulusSignalPlot->Legends->Add(legend1);
			this->stimulusSignalPlot->Location = System::Drawing::Point(6, 154);
			this->stimulusSignalPlot->Name = L"stimulusSignalPlot";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Legend = L"Legend1";
			series1->Name = L"Stimulus Signal";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->stimulusSignalPlot->Series->Add(series1);
			this->stimulusSignalPlot->Size = System::Drawing::Size(448, 156);
			this->stimulusSignalPlot->TabIndex = 27;
			this->stimulusSignalPlot->Text = L"stimulusSignalPlot";
			title1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title1->Name = L"xLabel";
			title1->Text = L"Time (s)";
			this->stimulusSignalPlot->Titles->Add(title1);
			// 
			// sineStimBiasUnitLabel
			// 
			this->sineStimBiasUnitLabel->AutoSize = true;
			this->sineStimBiasUnitLabel->Location = System::Drawing::Point(419, 108);
			this->sineStimBiasUnitLabel->Name = L"sineStimBiasUnitLabel";
			this->sineStimBiasUnitLabel->Size = System::Drawing::Size(41, 13);
			this->sineStimBiasUnitLabel->TabIndex = 26;
			this->sineStimBiasUnitLabel->Text = L"uN, um";
			// 
			// sineStimFrequencyUnitLabel
			// 
			this->sineStimFrequencyUnitLabel->AutoSize = true;
			this->sineStimFrequencyUnitLabel->Location = System::Drawing::Point(419, 85);
			this->sineStimFrequencyUnitLabel->Name = L"sineStimFrequencyUnitLabel";
			this->sineStimFrequencyUnitLabel->Size = System::Drawing::Size(20, 13);
			this->sineStimFrequencyUnitLabel->TabIndex = 25;
			this->sineStimFrequencyUnitLabel->Text = L"Hz";
			// 
			// sineStimBiasLabel
			// 
			this->sineStimBiasLabel->AutoSize = true;
			this->sineStimBiasLabel->Location = System::Drawing::Point(318, 108);
			this->sineStimBiasLabel->Name = L"sineStimBiasLabel";
			this->sineStimBiasLabel->Size = System::Drawing::Size(54, 13);
			this->sineStimBiasLabel->TabIndex = 24;
			this->sineStimBiasLabel->Text = L"Sine Bias:";
			// 
			// sineStimFrequencyLabel
			// 
			this->sineStimFrequencyLabel->AutoSize = true;
			this->sineStimFrequencyLabel->Location = System::Drawing::Point(288, 85);
			this->sineStimFrequencyLabel->Name = L"sineStimFrequencyLabel";
			this->sineStimFrequencyLabel->Size = System::Drawing::Size(84, 13);
			this->sineStimFrequencyLabel->TabIndex = 23;
			this->sineStimFrequencyLabel->Text = L"Sine Frequency:";
			// 
			// sineStimBiasText
			// 
			this->sineStimBiasText->Enabled = false;
			this->sineStimBiasText->Location = System::Drawing::Point(372, 105);
			this->sineStimBiasText->Name = L"sineStimBiasText";
			this->sineStimBiasText->Size = System::Drawing::Size(47, 20);
			this->sineStimBiasText->TabIndex = 22;
			// 
			// sineStimFrequencyText
			// 
			this->sineStimFrequencyText->Enabled = false;
			this->sineStimFrequencyText->Location = System::Drawing::Point(372, 83);
			this->sineStimFrequencyText->Name = L"sineStimFrequencyText";
			this->sineStimFrequencyText->Size = System::Drawing::Size(47, 20);
			this->sineStimFrequencyText->TabIndex = 21;
			// 
			// magnitudeStimUnitLabel
			// 
			this->magnitudeStimUnitLabel->AutoSize = true;
			this->magnitudeStimUnitLabel->Location = System::Drawing::Point(234, 85);
			this->magnitudeStimUnitLabel->Name = L"magnitudeStimUnitLabel";
			this->magnitudeStimUnitLabel->Size = System::Drawing::Size(41, 13);
			this->magnitudeStimUnitLabel->TabIndex = 20;
			this->magnitudeStimUnitLabel->Text = L"uN, um";
			// 
			// noCyclesStimUnitLabel
			// 
			this->noCyclesStimUnitLabel->AutoSize = true;
			this->noCyclesStimUnitLabel->Location = System::Drawing::Point(234, 64);
			this->noCyclesStimUnitLabel->Name = L"noCyclesStimUnitLabel";
			this->noCyclesStimUnitLabel->Size = System::Drawing::Size(37, 13);
			this->noCyclesStimUnitLabel->TabIndex = 19;
			this->noCyclesStimUnitLabel->Text = L"cycles";
			// 
			// dutyCycleStimUnitLabel
			// 
			this->dutyCycleStimUnitLabel->AutoSize = true;
			this->dutyCycleStimUnitLabel->Location = System::Drawing::Point(235, 42);
			this->dutyCycleStimUnitLabel->Name = L"dutyCycleStimUnitLabel";
			this->dutyCycleStimUnitLabel->Size = System::Drawing::Size(15, 13);
			this->dutyCycleStimUnitLabel->TabIndex = 18;
			this->dutyCycleStimUnitLabel->Text = L"%";
			// 
			// frequencyStimUnitLabel
			// 
			this->frequencyStimUnitLabel->AutoSize = true;
			this->frequencyStimUnitLabel->Location = System::Drawing::Point(234, 20);
			this->frequencyStimUnitLabel->Name = L"frequencyStimUnitLabel";
			this->frequencyStimUnitLabel->Size = System::Drawing::Size(20, 13);
			this->frequencyStimUnitLabel->TabIndex = 17;
			this->frequencyStimUnitLabel->Text = L"Hz";
			// 
			// scaleTypeStimLabel
			// 
			this->scaleTypeStimLabel->AutoSize = true;
			this->scaleTypeStimLabel->Location = System::Drawing::Point(97, 129);
			this->scaleTypeStimLabel->Name = L"scaleTypeStimLabel";
			this->scaleTypeStimLabel->Size = System::Drawing::Size(64, 13);
			this->scaleTypeStimLabel->TabIndex = 16;
			this->scaleTypeStimLabel->Text = L"Scale Type:";
			// 
			// scaleStimLabel
			// 
			this->scaleStimLabel->AutoSize = true;
			this->scaleStimLabel->Location = System::Drawing::Point(97, 108);
			this->scaleStimLabel->Name = L"scaleStimLabel";
			this->scaleStimLabel->Size = System::Drawing::Size(37, 13);
			this->scaleStimLabel->TabIndex = 15;
			this->scaleStimLabel->Text = L"Scale:";
			// 
			// scaleStimText
			// 
			this->scaleStimText->Enabled = false;
			this->scaleStimText->Location = System::Drawing::Point(174, 105);
			this->scaleStimText->Name = L"scaleStimText";
			this->scaleStimText->Size = System::Drawing::Size(58, 20);
			this->scaleStimText->TabIndex = 14;
			// 
			// scaleTypeStimComboBox
			// 
			this->scaleTypeStimComboBox->Enabled = false;
			this->scaleTypeStimComboBox->FormattingEnabled = true;
			this->scaleTypeStimComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Linear", L"Logarithmic"});
			this->scaleTypeStimComboBox->Location = System::Drawing::Point(174, 127);
			this->scaleTypeStimComboBox->Name = L"scaleTypeStimComboBox";
			this->scaleTypeStimComboBox->Size = System::Drawing::Size(121, 21);
			this->scaleTypeStimComboBox->TabIndex = 13;
			// 
			// magnitudeStimLabel
			// 
			this->magnitudeStimLabel->AutoSize = true;
			this->magnitudeStimLabel->Location = System::Drawing::Point(97, 85);
			this->magnitudeStimLabel->Name = L"magnitudeStimLabel";
			this->magnitudeStimLabel->Size = System::Drawing::Size(60, 13);
			this->magnitudeStimLabel->TabIndex = 12;
			this->magnitudeStimLabel->Text = L"Magnitude:";
			// 
			// noCyclesStimLabel
			// 
			this->noCyclesStimLabel->AutoSize = true;
			this->noCyclesStimLabel->Location = System::Drawing::Point(97, 64);
			this->noCyclesStimLabel->Name = L"noCyclesStimLabel";
			this->noCyclesStimLabel->Size = System::Drawing::Size(73, 13);
			this->noCyclesStimLabel->TabIndex = 11;
			this->noCyclesStimLabel->Text = L"No. of Cycles:";
			// 
			// customStimFileLabel
			// 
			this->customStimFileLabel->AutoSize = true;
			this->customStimFileLabel->Location = System::Drawing::Point(269, 15);
			this->customStimFileLabel->Name = L"customStimFileLabel";
			this->customStimFileLabel->Size = System::Drawing::Size(106, 13);
			this->customStimFileLabel->TabIndex = 10;
			this->customStimFileLabel->Text = L"Custom Stimulus File:";
			// 
			// dutyCycleStimLabel
			// 
			this->dutyCycleStimLabel->AutoSize = true;
			this->dutyCycleStimLabel->Location = System::Drawing::Point(97, 42);
			this->dutyCycleStimLabel->Name = L"dutyCycleStimLabel";
			this->dutyCycleStimLabel->Size = System::Drawing::Size(61, 13);
			this->dutyCycleStimLabel->TabIndex = 9;
			this->dutyCycleStimLabel->Text = L"Duty Cycle:";
			// 
			// frequencyStimLabel
			// 
			this->frequencyStimLabel->AutoSize = true;
			this->frequencyStimLabel->Location = System::Drawing::Point(97, 20);
			this->frequencyStimLabel->Name = L"frequencyStimLabel";
			this->frequencyStimLabel->Size = System::Drawing::Size(60, 13);
			this->frequencyStimLabel->TabIndex = 8;
			this->frequencyStimLabel->Text = L"Frequency:";
			// 
			// findCustomStimButton
			// 
			this->findCustomStimButton->Enabled = false;
			this->findCustomStimButton->Location = System::Drawing::Point(380, 53);
			this->findCustomStimButton->Name = L"findCustomStimButton";
			this->findCustomStimButton->Size = System::Drawing::Size(75, 23);
			this->findCustomStimButton->TabIndex = 7;
			this->findCustomStimButton->Text = L"Browse";
			this->findCustomStimButton->UseVisualStyleBackColor = true;
			this->findCustomStimButton->Click += gcnew System::EventHandler(this, &ExperimentSetUp::findCustomStimButton_Click);
			// 
			// customStimFileText
			// 
			this->customStimFileText->Enabled = false;
			this->customStimFileText->Location = System::Drawing::Point(266, 31);
			this->customStimFileText->Name = L"customStimFileText";
			this->customStimFileText->Size = System::Drawing::Size(189, 20);
			this->customStimFileText->TabIndex = 6;
			// 
			// magnitudeStimText
			// 
			this->magnitudeStimText->Enabled = false;
			this->magnitudeStimText->Location = System::Drawing::Point(174, 83);
			this->magnitudeStimText->Name = L"magnitudeStimText";
			this->magnitudeStimText->Size = System::Drawing::Size(58, 20);
			this->magnitudeStimText->TabIndex = 5;
			// 
			// noCyclesStimText
			// 
			this->noCyclesStimText->Enabled = false;
			this->noCyclesStimText->Location = System::Drawing::Point(174, 61);
			this->noCyclesStimText->Name = L"noCyclesStimText";
			this->noCyclesStimText->Size = System::Drawing::Size(58, 20);
			this->noCyclesStimText->TabIndex = 4;
			// 
			// dutyCycleStimText
			// 
			this->dutyCycleStimText->Enabled = false;
			this->dutyCycleStimText->Location = System::Drawing::Point(174, 39);
			this->dutyCycleStimText->Name = L"dutyCycleStimText";
			this->dutyCycleStimText->Size = System::Drawing::Size(58, 20);
			this->dutyCycleStimText->TabIndex = 3;
			// 
			// frequencyStimText
			// 
			this->frequencyStimText->Enabled = false;
			this->frequencyStimText->Location = System::Drawing::Point(174, 17);
			this->frequencyStimText->Name = L"frequencyStimText";
			this->frequencyStimText->Size = System::Drawing::Size(58, 20);
			this->frequencyStimText->TabIndex = 2;
			// 
			// showStimulusButton
			// 
			this->showStimulusButton->Location = System::Drawing::Point(342, 127);
			this->showStimulusButton->Name = L"showStimulusButton";
			this->showStimulusButton->Size = System::Drawing::Size(114, 23);
			this->showStimulusButton->TabIndex = 1;
			this->showStimulusButton->Text = L"Show Stimulus";
			this->showStimulusButton->UseVisualStyleBackColor = true;
			this->showStimulusButton->Click += gcnew System::EventHandler(this, &ExperimentSetUp::showStimulusButton_Click);
			// 
			// stimTypeGroupBox
			// 
			this->stimTypeGroupBox->Controls->Add(this->customStimRadioButton);
			this->stimTypeGroupBox->Controls->Add(this->sineStimRadioButton);
			this->stimTypeGroupBox->Controls->Add(this->triangleStimRadioButton);
			this->stimTypeGroupBox->Controls->Add(this->squareStimRadioButton);
			this->stimTypeGroupBox->Location = System::Drawing::Point(7, 20);
			this->stimTypeGroupBox->Name = L"stimTypeGroupBox";
			this->stimTypeGroupBox->Size = System::Drawing::Size(84, 118);
			this->stimTypeGroupBox->TabIndex = 0;
			this->stimTypeGroupBox->TabStop = false;
			this->stimTypeGroupBox->Text = L"Stimulus Type";
			// 
			// customStimRadioButton
			// 
			this->customStimRadioButton->AutoSize = true;
			this->customStimRadioButton->Location = System::Drawing::Point(11, 97);
			this->customStimRadioButton->Name = L"customStimRadioButton";
			this->customStimRadioButton->Size = System::Drawing::Size(60, 17);
			this->customStimRadioButton->TabIndex = 3;
			this->customStimRadioButton->TabStop = true;
			this->customStimRadioButton->Text = L"Custom";
			this->customStimRadioButton->UseVisualStyleBackColor = true;
			this->customStimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ExperimentSetUp::customStimRadioButton_CheckedChanged);
			// 
			// sineStimRadioButton
			// 
			this->sineStimRadioButton->AutoSize = true;
			this->sineStimRadioButton->Location = System::Drawing::Point(11, 74);
			this->sineStimRadioButton->Name = L"sineStimRadioButton";
			this->sineStimRadioButton->Size = System::Drawing::Size(46, 17);
			this->sineStimRadioButton->TabIndex = 2;
			this->sineStimRadioButton->TabStop = true;
			this->sineStimRadioButton->Text = L"Sine";
			this->sineStimRadioButton->UseVisualStyleBackColor = true;
			this->sineStimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ExperimentSetUp::sineStimRadioButton_CheckedChanged);
			// 
			// triangleStimRadioButton
			// 
			this->triangleStimRadioButton->AutoSize = true;
			this->triangleStimRadioButton->Location = System::Drawing::Point(11, 51);
			this->triangleStimRadioButton->Name = L"triangleStimRadioButton";
			this->triangleStimRadioButton->Size = System::Drawing::Size(63, 17);
			this->triangleStimRadioButton->TabIndex = 1;
			this->triangleStimRadioButton->TabStop = true;
			this->triangleStimRadioButton->Text = L"Triangle";
			this->triangleStimRadioButton->UseVisualStyleBackColor = true;
			this->triangleStimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ExperimentSetUp::triangleStimRadioButton_CheckedChanged);
			// 
			// squareStimRadioButton
			// 
			this->squareStimRadioButton->AutoSize = true;
			this->squareStimRadioButton->Location = System::Drawing::Point(11, 28);
			this->squareStimRadioButton->Name = L"squareStimRadioButton";
			this->squareStimRadioButton->Size = System::Drawing::Size(59, 17);
			this->squareStimRadioButton->TabIndex = 0;
			this->squareStimRadioButton->TabStop = true;
			this->squareStimRadioButton->Text = L"Square";
			this->squareStimRadioButton->UseVisualStyleBackColor = true;
			this->squareStimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &ExperimentSetUp::squareStimRadioButton_CheckedChanged);
			// 
			// customStimOpenFileDialog
			// 
			this->customStimOpenFileDialog->FileName = L"customStimFile";
			// 
			// ExperimentSetUp
			// 
			this->AcceptButton = this->confirmFormButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->closeFormButton;
			this->ClientSize = System::Drawing::Size(802, 633);
			this->Controls->Add(this->stimulusGroupBox);
			this->Controls->Add(this->cantileverGroupBox);
			this->Controls->Add(this->dataOutputGroupBox);
			this->Controls->Add(this->targetGroupBox);
			this->Controls->Add(this->experimentInfoGroupBox);
			this->Controls->Add(this->clampModeGroupBox);
			this->Controls->Add(this->confirmFormButton);
			this->Controls->Add(this->closeFormButton);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ExperimentSetUp";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Experiment Set Up";
			this->clampModeGroupBox->ResumeLayout(false);
			this->clampModeGroupBox->PerformLayout();
			this->experimentInfoGroupBox->ResumeLayout(false);
			this->experimentInfoGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->wormMapPictureBox))->EndInit();
			this->targetGroupBox->ResumeLayout(false);
			this->targetGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->targetTrackBar))->EndInit();
			this->dataOutputGroupBox->ResumeLayout(false);
			this->dataOutputGroupBox->PerformLayout();
			this->cantileverGroupBox->ResumeLayout(false);
			this->cantileverGroupBox->PerformLayout();
			this->stimulusGroupBox->ResumeLayout(false);
			this->stimulusGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->stimulusSignalPlot))->EndInit();
			this->stimTypeGroupBox->ResumeLayout(false);
			this->stimTypeGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion



private: System::Void confirmFormButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (experimentParameters->ExperimentTitle->Length == 0)
			 {	
				 MessageBox::Show("Experiment must have a title!");
				 return;
			 }
			 if (experimentParameters->WormStrain->Length == 0)
			 {	
				 MessageBox::Show("What strain worm are you using?");
				 return;
			 }
			if (experimentParameters->WormTreatments->Length == 0)
			 {	
				 MessageBox::Show("Did you use any treatments? If no, enter 'none'");
				 return;
			 }
			if (experimentParameters->PercentAgar->Length == 0)
			 {	
				 MessageBox::Show("What percent agar is the worm crawling on? Enter 0 if different substrate.");
				 return;
			 }
			if (experimentParameters->WormGender->Length == 0)
			 {	
				 MessageBox::Show("Please specify a gender");
				 return;
			 }
			if (experimentParameters->WormAge->Length == 0)
			 {	
				 MessageBox::Show("Please specify the worm's age");
				 return;
			 }
			if (experimentParameters->AmbientHumidity->Length == 0)
			 {	
				 MessageBox::Show("Please check the humidity in the room");
				 return;
			 }
			if (experimentParameters->AmbientTemperature->Length == 0)
			 {	
				 MessageBox::Show("Please check the temperature in the room");
				 return;
			 }
			if (experimentParameters->OtherInfo->Length == 0)
			 {	
				 MessageBox::Show("Please specify other notes, if none, enter 'none'");
				 return;
			 }
			if (experimentParameters->ExperimentMode->Length == 0)
			 {	
				 MessageBox::Show("Please specify an experiment mode");
				 return;
			 }
			if (experimentParameters->DataFileLocation->Length == 0)
			 {	
				 MessageBox::Show("Where do you want your data to go? Please specify!");
				 return;
			 }
			if (experimentParameters->WormTarget->Equals(0))
			{
				MessageBox::Show("Please specify a target");
				 return;
			}
			if (experimentParameters->CantileverFrequency->Equals(0))
			{
				MessageBox::Show("Please enter a valid device above");
				return;
			}
			if (experimentParameters->CantileverStiffness->Equals(0))
			{
				MessageBox::Show("Please enter a valid device above");
				return;
			}
			if (experimentParameters->CantileverSensitivity->Equals(0))
			{
				MessageBox::Show("Please enter a valid device above");
				return;
			}


			 
			 
			this->DialogResult = ::DialogResult::OK;
			this->Hide();
		 }
private: System::Void experimentTitleText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ experimentTitle = experimentTitleText->Text->Trim();
				 if (experimentTitle -> Length > 0)
				 {
					 experimentParameters->ExperimentTitle = experimentTitle;
				 }
		 }
private: System::Void wormStrainText_Validated(System::Object^  sender, System::EventArgs^  e) {
			String^ wormStrain = wormStrainText->Text->Trim();
			if (wormStrain->Length>0)
			{
				experimentParameters->WormStrain = wormStrain;
			}
		 }
private: System::Void wormTreatmentsText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ wormTreatments = wormTreatmentsText->Text->Trim();
			 if (wormTreatments ->Length >0)
			 {
				 experimentParameters->WormTreatments = wormTreatments;
			 }
		 }
private: System::Void percentAgarText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ percentAgar = percentAgarText->Text->Trim();
			 if (percentAgar->Length>0)
			 {
				 experimentParameters->PercentAgar = percentAgar;
			 }
		 }
private: System::Void wormGenderComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 String^ wormGender = wormGenderComboBox->Text->Trim();
			 if (wormGender->Length>0)
			 {	 
				experimentParameters->WormGender = wormGender;
			 }
		 }
private: System::Void wormAgeComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 String^ wormAge = wormAgeComboBox->Text->Trim();
			 if (wormAge->Length>0)
			 {	 
				experimentParameters->WormAge = wormAge;
			 }
		 }
private: System::Void ambientHumidityText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ ambientHumidity = ambientHumidityText->Text->Trim();
			 if (ambientHumidity->Length>0)
			 {
				 experimentParameters->AmbientHumidity = ambientHumidity;
			 }
		 }
private: System::Void ambientTemperatureText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ ambientTemperature = ambientTemperatureText->Text->Trim();
			 if (ambientTemperature->Length>0)
			 {
				 experimentParameters->AmbientTemperature = ambientTemperature;
			 }
		 }
private: System::Void otherInfoText_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ otherInfo = otherInfoText->Text->Trim();
			 if (otherInfo->Length>0)
			 {
				 experimentParameters->OtherInfo = otherInfo;
			 }
		 }
private: System::Void forceClampRadioButton_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ experimentMode = "ForceClamp";
			 experimentParameters->ExperimentMode = experimentMode;
		 }
private: System::Void displacementClampRadioButton_Validated(System::Object^  sender, System::EventArgs^  e) {
			 String^ experimentMode = "DisplacementClamp";
			 experimentParameters->ExperimentMode = experimentMode;
		 }

private: System::Void folderBrowserDialog_HelpRequest(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void fileBrowseButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (folderBrowserDialog->ShowDialog() == ::DialogResult::OK)
			 {
				dataOutputFileText->Text = folderBrowserDialog->SelectedPath;
				String^ fileName = folderBrowserDialog->SelectedPath;
				if (fileName->Length>0)
				{
					experimentParameters->DataFileLocation = fileName;
				}
			 }
		 }
private: System::Void targetTrackBar_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 targetValueLabel->Text = String::Concat(targetTrackBar->Value,"%");
			 Double^ wormTarget = Double(targetTrackBar->Value);
			 experimentParameters->WormTarget = wormTarget;
		 }


private: System::Void cantileverIDSearchButton_Click(System::Object^  sender, System::EventArgs^  e) {
			String^ waferID = waferIDText->Text->Trim();
			String^ deviceID = deviceIDText->Text->Trim();
			
			marshal_context^ context = gcnew marshal_context();
			const char* waferIDchar;
			waferIDchar = context->marshal_as<const char*>( waferID );

			const char* deviceIDchar;
			deviceIDchar = context->marshal_as<const char*>( deviceID );
		
			//look up in excel doc: function in "ExcelInterface.h"
			vector<double> specs = LookUpDevice(waferIDchar, deviceIDchar);
			if (specs[0] == -1)
			{
				MessageBox::Show("Please enter a valid WaferID");
				return;
			}
			else if (specs[0] == -2)
			{
				MessageBox::Show("Please enter a valid DeviceID");
				return;
			}
			

			//Set the text boxes to show values:
			String^ cantileverFrequency;
			stringstream ss0;
			ss0 << specs[0];
			cantileverFrequency = marshal_as<String^>(ss0.str().c_str());
			cantileverFrequencyText->Text = cantileverFrequency;

			String^ cantileverStiffness;
			stringstream ss1;
			ss1 << specs[1];
			cantileverStiffness = marshal_as<String^>(ss1.str().c_str());
			cantileverStiffnessText->Text = cantileverStiffness;

			String^ cantileverSensitivity;
			stringstream ss2;
			ss2 << specs[2];
			cantileverSensitivity = marshal_as<String^>(ss2.str().c_str());
			cantileverSensitivityText->Text = cantileverSensitivity;

			//set to parameters class.
			experimentParameters->CantileverFrequency = specs[0];
			experimentParameters->CantileverStiffness = specs[1];
			experimentParameters->CantileverSensitivity = specs[2];

			experimentParameters->CantileverID = waferID+deviceID;
		 }
		 

private: System::Void findCustomStimButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(customStimOpenFileDialog->ShowDialog() == ::DialogResult::OK)
			  {
				  customStimFileText->Text = customStimOpenFileDialog->FileName;
			  }
		 }

private: System::Void customStimRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (customStimRadioButton->Checked == true)
			 {
				customStimFileText->Enabled = true;
				findCustomStimButton->Enabled = true;
			}
			 else
			 {
				customStimFileText->Enabled = false;
				findCustomStimButton->Enabled = false;
			 }
		 }
private: System::Void squareStimRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (squareStimRadioButton->Checked == true || triangleStimRadioButton->Checked == true || sineStimRadioButton->Checked == true)
			 {
				frequencyStimText->Enabled = true;
				dutyCycleStimText->Enabled = true;
				noCyclesStimText->Enabled = true;
				magnitudeStimText->Enabled = true;
				scaleStimText->Enabled = true;
				scaleTypeStimComboBox->Enabled = true;
			}
			else
			{
				frequencyStimText->Enabled = false;
				dutyCycleStimText->Enabled = false;
				noCyclesStimText->Enabled = false;
				magnitudeStimText->Enabled = false;
				scaleStimText->Enabled = false;
				scaleTypeStimComboBox->Enabled = false;
			}
		 }
private: System::Void triangleStimRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (squareStimRadioButton->Checked == true || triangleStimRadioButton->Checked == true || sineStimRadioButton->Checked == true)
			{
				frequencyStimText->Enabled = true;
				dutyCycleStimText->Enabled = true;
				noCyclesStimText->Enabled = true;
				magnitudeStimText->Enabled = true;
				scaleStimText->Enabled = true;
				scaleTypeStimComboBox->Enabled = true;
			}
			else
			{
				frequencyStimText->Enabled = false;
				dutyCycleStimText->Enabled = false;
				noCyclesStimText->Enabled = false;
				magnitudeStimText->Enabled = false;
				scaleStimText->Enabled = false;
				scaleTypeStimComboBox->Enabled = false;			 
			}
		 }
private: System::Void sineStimRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (sineStimRadioButton->Checked == true) 
			{
				frequencyStimText->Enabled = true;
				dutyCycleStimText->Enabled = true;
				noCyclesStimText->Enabled = true;
				magnitudeStimText->Enabled = true;
				scaleStimText->Enabled = true;
				scaleTypeStimComboBox->Enabled = true;
				sineStimFrequencyText->Enabled = true;
				sineStimBiasText->Enabled = true;
			}
			else if(triangleStimRadioButton->Checked == true || sineStimRadioButton->Checked == true)
			{
				frequencyStimText->Enabled = true;
				dutyCycleStimText->Enabled = true;
				noCyclesStimText->Enabled = true;
				magnitudeStimText->Enabled = true;
				scaleStimText->Enabled = true;
				scaleTypeStimComboBox->Enabled = true;
				sineStimFrequencyText->Enabled = false;
				sineStimBiasText->Enabled = false;
			}
			else
			{
				frequencyStimText->Enabled = false;
				dutyCycleStimText->Enabled = false;
				noCyclesStimText->Enabled = false;
				magnitudeStimText->Enabled = false;
				scaleStimText->Enabled = false;
				scaleTypeStimComboBox->Enabled = false;
				sineStimFrequencyText->Enabled = false;
				sineStimBiasText->Enabled = false;
			}
		 }
private: System::Void showStimulusButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			this->stimulusSignalPlot->Series["Stimulus Signal"]->Points->Clear();
			 
			if (customStimRadioButton->Checked == false)
			{ 
				//convert all input string to double for mathematical manupulation.			
				Double frequency;
				Double dutyCycle;
				Double noCycles;
				Double magnitude;
				Double scale;
				Double sineFrequency;
				Double sineBias;

				bool checkFrequency = Double::TryParse(frequencyStimText->Text, frequency);
				bool checkDutyCycle = Double::TryParse(dutyCycleStimText->Text, dutyCycle);
				bool checkNoCycles = Double::TryParse(noCyclesStimText->Text, noCycles);
				bool checkMagnitude = Double::TryParse(magnitudeStimText->Text, magnitude);
				bool checkScale = Double::TryParse(scaleStimText->Text, scale);
				bool checkSineFrequency = Double::TryParse(sineStimFrequencyText->Text, sineFrequency);
				bool checkSineBias = Double::TryParse(sineStimBiasText->Text, sineBias);
				// if any aren't digits, give an error message.
				if(!checkFrequency || !checkDutyCycle || !checkNoCycles || !checkMagnitude || !checkScale )
				{
					MessageBox::Show("Please only enter numbers!");
					return;
				}
				
				int scaleType;
				if (scaleTypeStimComboBox->Text == "Linear")
				{
					scaleType = 1;
				}
				else if (scaleTypeStimComboBox->Text == "Logarithmic")
				{
					scaleType = 2;
				}


				
				// now create stimulus based on type chosen.
				//Square
				if (squareStimRadioButton->Checked)
				{
					StimulusControl Stimulus(frequency, dutyCycle, noCycles, magnitude, scale, scaleType);
					Stimulus.CreateSquare();
					for (int i=0; i<Stimulus.TimeArray.Length; i++)
					{
						this->stimulusSignalPlot->Series["Stimulus Signal"]->Points->AddXY(Stimulus.TimeArray[i],Stimulus.MagnitudeArray[i]);
					}
					experimentParameters->TimeStimulusSignal = Stimulus.TimeArray;
					experimentParameters->MagnitudeStimulusSignal = Stimulus.MagnitudeArray;			
				}
				//triangle
				else if(triangleStimRadioButton->Checked)
				{
					StimulusControl Stimulus(frequency, dutyCycle, noCycles, magnitude, scale, scaleType);	
					Stimulus.CreateTriangle();
					for (int i=0; i<Stimulus.TimeArray.Length; i++)
					{
						this->stimulusSignalPlot->Series["Stimulus Signal"]->Points->AddXY(Stimulus.TimeArray[i],Stimulus.MagnitudeArray[i]);
					}					
					experimentParameters->TimeStimulusSignal = Stimulus.TimeArray;
					experimentParameters->MagnitudeStimulusSignal = Stimulus.MagnitudeArray;
				}
				//sine
				else if(sineStimRadioButton->Checked)
				{
					StimulusControl Stimulus(frequency, dutyCycle, noCycles, magnitude, scale, scaleType, sineFrequency, sineBias);				
					Stimulus.CreateSine();
					for (int i=0; i<Stimulus.TimeArray.Length; i++)
					{
						this->stimulusSignalPlot->Series["Stimulus Signal"]->Points->AddXY(Stimulus.TimeArray[i],Stimulus.MagnitudeArray[i]);
					}
					experimentParameters->TimeStimulusSignal = Stimulus.TimeArray;
					experimentParameters->MagnitudeStimulusSignal = Stimulus.MagnitudeArray;
				}
				
			}
			else if(customStimRadioButton->Checked == true)
			{	
				StimulusControl Stimulus;
				if (customStimFileText->Text->Length > 0)
				{
					if (Stimulus.ReadCustomFile(customStimFileText->Text) == 0)
					{
						for (int i=0; i<Stimulus.TimeArray.Length; i++)
						{
							this->stimulusSignalPlot->Series["Stimulus Signal"]->Points->AddXY(Stimulus.TimeArray[i],Stimulus.MagnitudeArray[i]);
						}
						experimentParameters->TimeStimulusSignal = Stimulus.TimeArray;
						experimentParameters->MagnitudeStimulusSignal = Stimulus.MagnitudeArray;	
					}
					else
					{
						MessageBox::Show("Could not read in stimulus file, please enter a valid file.");
					}

				}
				else 
				{
					MessageBox::Show("Please enter a valid file for custom stimulus");
					return;
				}

				

			}

		}

};
}
