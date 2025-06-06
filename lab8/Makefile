SRC_DIR := src
TARGET_DIR := target
GNUPLOT_DIR := plots/gnuplot-files
REPORT_DIR := report

GROUP_ID := com.heaps
ARTIFACT_ID := lab8
JAR_FILE := $(ARTIFACT_ID)-1.0-SNAPSHOT.jar
CLASS_NAME := $(GROUP_ID).Main

RPRT := $(REPORT_DIR)/report.pdf
EXE := $(TARGET_DIR)/$(JAR_FILE)
GNP := $(wildcard $(GNUPLOT_DIR)/*.p)

JV := java
JVFLAGS := -cp 
PARAMETERS := -XX:+DisableExplicitGC
MEMORY_SIZE := -Xmx1G
MVN := mvn

GNPLT := gnuplot
ZTHR := zathura
PDFLTX := pdflatex

OUTPUT := --output-directory

.PHONY: all

all: clean-report run-src compile-gnp run-report clean-aux clean-target

run-src: $(EXE)
	@echo "Running.."
	@$(JV) $(PARAMETERS) $(MEMORY_SIZE) $(JVFLAGS) $< $(CLASS_NAME)

$(EXE):
	@echo "Building binaries.."
	@$(MVN) install

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
	@$(MVN) clean

clean-report:
	@echo "Cleaning the report.."
	@$(RM) $(RPRT)
