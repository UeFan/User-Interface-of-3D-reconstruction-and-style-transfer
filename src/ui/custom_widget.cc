// COLMAP - Structure-from-Motion and Multi-View Stereo.
// Copyright (C) 2017  Johannes L. Schoenberger <jsch at inf.ethz.ch>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "ui/custom_widget.h"

#include "ui/options_widget.h"
#include "ui/qt_utils.h"
#include "ui/thread_control_widget.h"

namespace colmap {

CustomWidget::CustomWidget(QWidget* parent, OptionManager* options)
    : QWidget(parent), options_(options), prev_selected_(false) {
  setWindowFlags(Qt::Dialog);
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Custom");
  // Database path.
  QPushButton* databse_path_new = new QPushButton(tr("New"), this);
  connect(databse_path_new, &QPushButton::released, this,
          &CustomWidget::SelectNewDatabasePath);
  QPushButton* databse_path_open = new QPushButton(tr("Open"), this);
  connect(databse_path_open, &QPushButton::released, this,
          &CustomWidget::SelectExistingDatabasePath);

  test_qlabel = new QLabel(tr("asd"),this);
  //test_qlabel->setText(nd);

  database_path_text_ = new QLineEdit(this);
  database_path_text_->setText(
      QString::fromStdString(*options_->database_path));

  // Image path.
  QPushButton* image_path_select = new QPushButton(tr("Select"), this);
  connect(image_path_select, &QPushButton::released, this,
          &CustomWidget::SelectImagePath);
  image_path_text_ = new QLineEdit(this);
  image_path_text_->setText(QString::fromStdString(*options_->image_path));

  // Save button.
  QPushButton* create_button = new QPushButton(tr("Save"), this);
  connect(create_button, &QPushButton::released, this, &CustomWidget::Save);

  QGridLayout* grid = new QGridLayout(this);

  grid->addWidget(new QLabel(tr("Database"), this), 0, 0);
  grid->addWidget(database_path_text_, 0, 1);
  grid->addWidget(databse_path_new, 0, 2);
  grid->addWidget(databse_path_open, 0, 3);

  grid->addWidget(new QLabel(tr("Images"), this), 1, 0);
  grid->addWidget(image_path_text_, 1, 1);
  grid->addWidget(image_path_select, 1, 2);


  grid->addWidget(new QLabel(tr("->_path"), this), 2, 0);

  grid->addWidget(test_qlabel, 2, 1);
  grid->addWidget(create_button, 2, 2);
}

bool CustomWidget::IsValid() const {
  return ExistsDir(ImagePath()) && !ExistsDir(DatabasePath()) &&
         ExistsDir(GetParentDir(DatabasePath()));
}

void CustomWidget::Reset() {
  database_path_text_->clear();
  image_path_text_->clear();
}

std::string CustomWidget::DatabasePath() const {
  return database_path_text_->text().toUtf8().constData();
}

std::string CustomWidget::ImagePath() const {
  return image_path_text_->text().toUtf8().constData();
}

void CustomWidget::SetDatabasePath(const std::string& path) {
  database_path_text_->setText(QString::fromStdString(path));
  //test_qlabel->setText(QString::fromStdString(path));

}

void CustomWidget::SetImagePath(const std::string& path) {
  image_path_text_->setText(QString::fromStdString(path));
}

bool CustomWidget::NewProjectOneClick()
{
    QString database_path = QFileDialog::getSaveFileName(
        this, tr("Select database file"), DefaultDirectory(),
        tr("SQLite3 database (*.db)"));
    if (database_path != "" &&
        !HasFileExtension(database_path.toUtf8().constData(), ".db")) {
      database_path += ".db";
    }
    *options_->database_path = database_path.toStdString();

    QString image_path = QFileDialog::getExistingDirectory(
                                      this, tr("Select image path..."), DefaultDirectory(),
                                      QFileDialog::ShowDirsOnly);
    *options_->image_path = image_path.toStdString();
    
    // Save empty database file.
    Database database(*options_->database_path);
    return ExistsDir(*options_->image_path) && !ExistsDir(*options_->database_path) &&
             ExistsDir(GetParentDir(*options_->database_path));

}

void CustomWidget::Save() {
  if (IsValid()) {
    *options_->database_path = DatabasePath();
    *options_->image_path = ImagePath();

    // Save empty database file.
    Database database(*options_->database_path);

    hide();
  } else {
    QMessageBox::critical(this, "", tr("Invalid paths"));
  }
}

void CustomWidget::SelectNewDatabasePath() {
  QString database_path = QFileDialog::getSaveFileName(
      this, tr("Select database file"), DefaultDirectory(),
      tr("SQLite3 database (*.db)"));
  if (database_path != "" &&
      !HasFileExtension(database_path.toUtf8().constData(), ".db")) {
    database_path += ".db";
  }
  database_path_text_->setText(database_path);
  test_qlabel->setText(database_path);

}

void CustomWidget::SelectExistingDatabasePath() {
  database_path_text_->setText(QFileDialog::getOpenFileName(
      this, tr("Select database file"), DefaultDirectory(),
      tr("SQLite3 database (*.db)")));
}

void CustomWidget::SelectImagePath() {
  image_path_text_->setText(QFileDialog::getExistingDirectory(
      this, tr("Select image path..."), DefaultDirectory(),
      QFileDialog::ShowDirsOnly));
}

QString CustomWidget::DefaultDirectory() {
  std::string directory_path = "";
  if (!prev_selected_ && !options_->project_path->empty()) {
    const auto parent_path = GetParentDir(*options_->project_path);
    if (ExistsDir(parent_path)) {
      directory_path = parent_path;
    }
  }
  prev_selected_ = true;
  return QString::fromStdString(directory_path);
}

////////////////////////////////////////////////////////////////////////////
///////////custom feature extraction
////////////////////////////////////////////////////////////////////////////
  
//class CustomExtractionWidget : public OptionsWidget {
//  public:
//    CustomExtractionWidget(QWidget* parent, OptionManager* options);
    
//    virtual void Run() = 0;
    
//  protected:
//    OptionManager* options_;
//    ThreadControlWidget* thread_control_widget_;
//  };
  
//class CustomSIFTExtractionWidget : public CustomExtractionWidget {
//  public:
//    CustomSIFTExtractionWidget(QWidget* parent, OptionManager* options);
    
//    void Run() override;
    
//  private:
//    QRadioButton* sift_gpu_;
//    QRadioButton* sift_cpu_;
//  };
  
//class CustomImportFeaturesWidget : public CustomExtractionWidget {
//  public:
//    CustomImportFeaturesWidget(QWidget* parent, OptionManager* options);
    
//    void Run() override;
    
//  private:
//    std::string import_path_;
//  };
  
//CustomExtractionWidget::CustomExtractionWidget(QWidget* parent, OptionManager* options)
//  : OptionsWidget(parent),
//  options_(options),
//  thread_control_widget_(new ThreadControlWidget(this)) {}
  
//CustomSIFTExtractionWidget::CustomSIFTExtractionWidget(QWidget* parent,
//                                                         OptionManager* options)
//  : CustomExtractionWidget(parent, options) {
//    sift_gpu_ = new QRadioButton(tr("GPU"), this);
//    sift_gpu_->setChecked(true);
//    grid_layout_->addWidget(sift_gpu_);
//    grid_layout_->addWidget(sift_gpu_, grid_layout_->rowCount(), 1);
    
//    sift_cpu_ = new QRadioButton(tr("CPU"), this);
//    grid_layout_->addWidget(sift_cpu_, grid_layout_->rowCount(), 1);
    
//    AddSpacer();
    
//    AddOptionInt(&options->sift_extraction->max_image_size, "max_image_size");
//    AddOptionInt(&options->sift_extraction->max_num_features, "max_num_features");
//    AddOptionInt(&options->sift_extraction->first_octave, "first_octave", -5);
//    AddOptionInt(&options->sift_extraction->num_octaves, "num_octaves");
//    AddOptionInt(&options->sift_extraction->octave_resolution,
//                 "octave_resolution");
//    AddOptionDouble(&options->sift_extraction->peak_threshold, "peak_threshold",
//                    0.0, 1e7, 0.0001, 4);
//    AddOptionDouble(&options->sift_extraction->edge_threshold, "edge_threshold");
//    AddOptionInt(&options->sift_extraction->max_num_orientations,
//                 "max_num_orientations");
//    AddOptionBool(&options->sift_extraction->upright, "upright");
    
//    AddOptionInt(&options->sift_gpu_extraction->index, "gpu_index", -1);
    
//    AddOptionInt(&options->sift_cpu_extraction->num_threads, "cpu_num_threads",
//                 -1);
//    AddOptionInt(&options->sift_cpu_extraction->batch_size_factor,
//                 "cpu_batch_size_factor");
//  }
  
//void CustomSIFTExtractionWidget::Run() {
//    WriteOptions();
    
//    ImageReader::Options reader_options = *options_->image_reader;
//    reader_options.database_path = *options_->database_path;
//    reader_options.image_path = *options_->image_path;
    
//    Thread* extractor = nullptr;
//    if (sift_gpu_->isChecked()) {
//      extractor =
//      new SiftGPUFeatureExtractor(reader_options, *options_->sift_extraction,
//                                  *options_->sift_gpu_extraction);
//    } else {
//      extractor =
//      new SiftCPUFeatureExtractor(reader_options, *options_->sift_extraction,
//                                  *options_->sift_cpu_extraction);
//    }
    
//    thread_control_widget_->StartThread("Extracting...", true, extractor);
//}
  
//CustomImportFeaturesWidget::CustomImportFeaturesWidget(QWidget* parent,
//                                             OptionManager* options)
//  : CustomExtractionWidget(parent, options) {
//    AddOptionDirPath(&import_path_, "import_path");
//}
  
//void CustomImportFeaturesWidget::Run() {
//    WriteOptions();
    
//    if (!ExistsDir(import_path_)) {
//      QMessageBox::critical(this, "", tr("Path is not a directory"));
//      return;
//    }
    
//    ImageReader::Options reader_options = *options_->image_reader;
//    reader_options.database_path = *options_->database_path;
//    reader_options.image_path = *options_->image_path;
    
//    Thread* importer = new FeatureImporter(reader_options, import_path_);
//    thread_control_widget_->StartThread("Importing...", true, importer);
//  }
  
//CustomFeatureExtractionWidget::CustomFeatureExtractionWidget(QWidget* parent,
//                                                   OptionManager* options)
//  : parent_(parent), options_(options) {
//    // Do not change flag, to make sure feature database is not accessed from
//    // multiple threads
//    setWindowFlags(Qt::Window);
//    setWindowTitle("Feature extraction");
    
//    QGridLayout* grid = new QGridLayout(this);
    
//    grid->addWidget(CreateCameraModelBox(), 0, 0);
    
//    tab_widget_ = new QTabWidget(this);
//    tab_widget_->addTab(new CustomSIFTExtractionWidget(this, options), tr("Extract"));
//    tab_widget_->addTab(new CustomImportFeaturesWidget(this, options), tr("Import"));
//    grid->addWidget(tab_widget_);
    
//    QPushButton* extract_button = new QPushButton(tr("Extract"), this);
//    connect(extract_button, &QPushButton::released, this,
//            &CustomFeatureExtractionWidget::Extract);
//    grid->addWidget(extract_button, grid->rowCount(), 0);
//  }
  
//QGroupBox* CustomFeatureExtractionWidget::CreateCameraModelBox() {
//    camera_model_ids_.clear();
    
//    camera_model_cb_ = new QComboBox(this);
    
//#define CAMERA_MODEL_CASE(CameraModel)                                     \
//    camera_model_cb_->addItem(                                               \
//                              QString::fromStdString(CameraModelIdToName(CameraModel::model_id))); \
//    camera_model_ids_.push_back(static_cast<int>(CameraModel::model_id));
    
//    CAMERA_MODEL_CASES
    
//#undef CAMERA_MODEL_CASE
    
//    camera_params_exif_rb_ = new QRadioButton(tr("Parameters from EXIF"), this);
//    camera_params_exif_rb_->setChecked(true);
    
//    camera_params_custom_rb_ = new QRadioButton(tr("Custom parameters"), this);
    
//    camera_params_info_ = new QLabel(tr(""), this);
//    QPalette pal = QPalette(camera_params_info_->palette());
//    pal.setColor(QPalette::WindowText, QColor(130, 130, 130));
//    camera_params_info_->setPalette(pal);
    
//    camera_params_text_ = new QLineEdit(this);
//    camera_params_text_->setEnabled(false);
    
//    single_camera_cb_ = new QCheckBox("Shared for all images", this);
//    single_camera_cb_->setChecked(false);
    
//    QGroupBox* box = new QGroupBox(tr("Camera model"), this);
    
//    QVBoxLayout* vbox = new QVBoxLayout(box);
//    vbox->addWidget(camera_model_cb_);
//    vbox->addWidget(camera_params_info_);
//    vbox->addWidget(single_camera_cb_);
//    vbox->addWidget(camera_params_exif_rb_);
//    vbox->addWidget(camera_params_custom_rb_);
//    vbox->addWidget(camera_params_text_);
//    vbox->addStretch(1);
    
//    box->setLayout(vbox);
    
//    SelectCameraModel(camera_model_cb_->currentIndex());
    
//    connect(camera_model_cb_,
//            (void (QComboBox::*)(int)) & QComboBox::currentIndexChanged, this,
//            &CustomFeatureExtractionWidget::SelectCameraModel);
//    connect(camera_params_exif_rb_, &QRadioButton::clicked, camera_params_text_,
//            &QLineEdit::setDisabled);
//    connect(camera_params_custom_rb_, &QRadioButton::clicked, camera_params_text_,
//            &QLineEdit::setEnabled);
    
//    return box;
//}
  
//void CustomFeatureExtractionWidget::showEvent(QShowEvent* event) {
//    parent_->setDisabled(true);
//    ReadOptions();
//}
  
//void CustomFeatureExtractionWidget::hideEvent(QHideEvent* event) {
//    parent_->setEnabled(true);
//    WriteOptions();
//}
  
//void CustomFeatureExtractionWidget::ReadOptions() {
//    const auto camera_code =
//    CameraModelNameToId(options_->image_reader->camera_model);
//    for (size_t i = 0; i < camera_model_ids_.size(); ++i) {
//      if (camera_model_ids_[i] == camera_code) {
//        SelectCameraModel(i);
//        camera_model_cb_->setCurrentIndex(i);
//        break;
//      }
//    }
//    single_camera_cb_->setChecked(options_->image_reader->single_camera);
//    camera_params_text_->setText(
//                                 QString::fromStdString(options_->image_reader->camera_params));
//}
  
//void CustomFeatureExtractionWidget::WriteOptions() {
//    options_->image_reader->camera_model =
//    CameraModelIdToName(camera_model_ids_[camera_model_cb_->currentIndex()]);
//    options_->image_reader->single_camera = single_camera_cb_->isChecked();
//    options_->image_reader->camera_params =
//    camera_params_text_->text().toUtf8().constData();
//}
  
//void CustomFeatureExtractionWidget::SelectCameraModel(const int idx) {
//    const int code = camera_model_ids_[idx];
//    camera_params_info_->setText(QString::fromStdString(StringPrintf(
//                                                                     "<small>Parameters: %s</small>", CameraModelParamsInfo(code).c_str())));
//}
  
//void CustomFeatureExtractionWidget::Extract() {
//    // If the custom parameter radiobuttion is not checked, but the
//    // parameters textbox contains parameters.
//    const auto old_camera_params_text = camera_params_text_->text();
//    if (!camera_params_custom_rb_->isChecked()) {
//      camera_params_text_->setText("");
//    }
    
//    WriteOptions();
    
//    const std::vector<double> camera_params =
//    CSVToVector<double>(options_->image_reader->camera_params);
//    const auto camera_code =
//    CameraModelNameToId(options_->image_reader->camera_model);
    
//    if (camera_params_custom_rb_->isChecked() &&
//        !CameraModelVerifyParams(camera_code, camera_params)) {
//      QMessageBox::critical(this, "", tr("Invalid camera parameters"));
//      return;
//    }
    
//    static_cast<CustomExtractionWidget*>(tab_widget_->currentWidget())->Run();
    
//    camera_params_text_->setText(old_camera_params_text);
//}

 
 
 
 
}  // namespace colmap
