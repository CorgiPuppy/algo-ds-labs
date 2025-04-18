SRC_DIR := src
TARGET_DIR := target
GNUPLOT_DIR := plots/gnuplot-files
REPORT_DIR := report

GROUP_ID := com.heaps
ARTIFACT_ID := lab8
JAR_FILE := $(ARTIFACT_ID)-1.0-SNAPSHOT.jar
CLASS_NAME := $(GROUP_ID).App

RPRT := $(REPORT_DIR)/report.pdf
EXE := $(TARGET_DIR)/$(JAR_FILE)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC))
GNP := $(wildcard $(GNUPLOT_DIR)/*.p)

JV := java
JVFLAGS := -cp 
MVN := mvn
GNPLT := gnuplot
ZTHR := zathura
PDFLTX := pdflatex

OUTPUT := --output-directory

.PHONY: all

all: clean-report run-src compile-gnp run-report clean-aux clean-target

run-src: $(EXE)
	@echo "Running.."
	$(JV) $(JVFLAGS) $< $(CLASS_NAME)

$(EXE):
	@echo "Building binaries.."
	@$(MVN) clean install

compile-gnp: $(GNP)
	@echo "Compile gnuplot files.."
	@$(foreach file_name, $(GNP), $(GNPLT) $(file_name);)

run-report: $(RPRT)
	@echo "Running a report.."
	@$(ZTHR) $<

$(RPRT): $(REPORT_DIR)/*.tex
	@echo "Building pdf.."	
	@$(PDFLTX) $(OUTPUT)=$(REPORT_DIR) $<
	@$(PDFLTX) $(OUTPUT)=$(REPORT_DIR) $<

clean-aux:
	@echo "Cleaning up auxiliary files.."
	@find $(REPORT_DIR) -type f ! -name '*.pdf' ! -name '*.tex' -delete

clean-target:
	@echo "Cleaning the target dir.."
	@$(RM) -rv $(TARGET_DIR)

clean-report:
	@echo "Cleaning the report.."
	@$(RM) $(RPRT)
