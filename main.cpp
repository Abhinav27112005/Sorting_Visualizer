#include <wx/wx.h>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>

class SortVisualizerFrame: public wxFrame {
public:
    SortVisualizerFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size), numbersToSort(100) {

        // Initialize the GUI components
        wxPanel* panel = new wxPanel(this, wxID_ANY,wxDefaultPosition,wxDefaultSize,wxBORDER_SIMPLE);

        generateButton = new wxButton(panel, wxID_ANY, "Generate Numbers");
        sortButton = new wxButton(panel, wxID_ANY, "Bubble sort");
        quicksortButton = new wxButton(panel, wxID_ANY, "Quick Sort");
        MergeSortButton = new wxButton(panel, wxID_ANY, "Merge Sort");
        radixSortButton = new wxButton(panel, wxID_ANY, "Radix Sort");
        insertionsortButton = new wxButton(panel, wxID_ANY, "Insertion Sort");
        selectionsortButton = new wxButton(panel, wxID_ANY, "Selection Sort");
        heapSortButton = new wxButton(panel, wxID_ANY, "Heap Sort");
        shellsortButton = new wxButton(panel, wxID_ANY, "Shell Sort");
        combsortButton = new wxButton(panel, wxID_ANY, "Comb Sort");
        cyclesortButton = new wxButton(panel, wxID_ANY, "Cycle Sort");

        canvas = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(800, 400),wxBORDER_SIMPLE);
        canvas->SetBackgroundColour(wxColor(0, 0, 0));

        wxBoxSizer* buttonsizer = new wxBoxSizer(wxHORIZONTAL);
        buttonsizer->Add(generateButton, 1, wxALL , 5);
        buttonsizer->Add(sortButton, 1, wxALL, 5);
        buttonsizer->Add(quicksortButton, 1, wxALL, 5);
        buttonsizer->Add(MergeSortButton, 1, wxALL, 5);
        buttonsizer->Add(radixSortButton, 1, wxALL, 5);
        buttonsizer->Add(insertionsortButton, 1, wxALL, 5);
        buttonsizer->Add(selectionsortButton, 1, wxALL, 5);
        buttonsizer->Add(heapSortButton, 1, wxALL, 5);
        buttonsizer->Add(shellsortButton, 1, wxALL, 5);
        buttonsizer->Add(combsortButton, 1, wxALL, 5);
        buttonsizer->Add(cyclesortButton, 1, wxALL, 5);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(canvas, 1, wxEXPAND | wxALL, 5);
        sizer->Add(buttonsizer, 0, wxALL|wxEXPAND, 5);
        panel->SetSizerAndFit(sizer);

        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnGenerateNumbers, this, generateButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnSort, this, sortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnQuickSort,this,quicksortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnMergeSort, this, MergeSortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnRadixSort, this, radixSortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnInsertionSort, this, insertionsortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnSelectionSort, this, selectionsortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnHeapSort, this, heapSortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnShellSort, this, shellsortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnCombSort, this, combsortButton->GetId());
        Bind(wxEVT_BUTTON, &SortVisualizerFrame::OnCycleSort, this, cyclesortButton->GetId());

        // Initialize random number generator
        std::random_device rd;
        randGen = std::mt19937(rd());
        dist = std::uniform_int_distribution<int>(1, 400);

        ResetCanvas();
    }

private:
    wxButton* generateButton;
    wxButton* sortButton;
    wxButton* quicksortButton;
    wxButton* MergeSortButton;
    wxButton* radixSortButton;
    wxButton* insertionsortButton;
    wxButton* selectionsortButton;
    wxButton* heapSortButton;
    wxButton* shellsortButton;
    wxButton* combsortButton;
    wxButton* cyclesortButton;

    wxPanel* canvas;
    std::vector<int> numbersToSort;
    std::mt19937 randGen;
    std::uniform_int_distribution<int> dist;

    void ResetCanvas() {
        wxClientDC dc(canvas);
        dc.SetBackground(wxBrush(wxColour(0, 0,0)));
        dc.Clear();
    }

    void DrawNumbers(int swapno=0,int swapo=0) {
        wxClientDC dc(canvas);
        dc.Clear();
        int width = canvas->GetSize().GetWidth();
        int height = canvas->GetSize().GetHeight();
        int barWidth = width / numbersToSort.size();

        for (size_t i = 0; i < numbersToSort.size(); ++i) {
            int x = i * barWidth;
            int barHeight = (numbersToSort[i] * height) / 400;
            dc.SetBrush(wxBrush(wxColour(0, 0, 255)));
            if (i == swapno && swapno != 0 || i == swapo && swapo != 0)
            {
                dc.SetBrush(wxBrush(wxColour(255, 255, 255)));
                dc.DrawRectangle(x, height - barHeight, barWidth, barHeight);
                continue;
            }
            dc.DrawRectangle(x, height - barHeight, barWidth, barHeight);
        }
    }

    void BubbleSort() {
        int n = numbersToSort.size();
        bool swapped;
        do {
            swapped = false;
            for (int i = 1; i < n; ++i) {
                if (numbersToSort[i - 1] > numbersToSort[i]) {
                    std::swap(numbersToSort[i - 1], numbersToSort[i]);
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                    DrawNumbers(i-1,i);
                    wxYield();
                    swapped = true;
                }
            }
        } while (swapped);
    }

    void OnGenerateNumbers(wxCommandEvent& event) {
        for (int& num : numbersToSort) {
            num = dist(randGen);
        }
        ResetCanvas();
        DrawNumbers();
    }

    void OnSort(wxCommandEvent& event) {
        std::thread sortingThread(&SortVisualizerFrame::BubbleSort, this);
        sortingThread.detach();
    }
    void QuickSort(int left, int right) {
        if (left < right) {
            int pivotIndex = Partition(left, right);
            QuickSort(left, pivotIndex - 1);
            QuickSort(pivotIndex + 1, right);
        }
    }

    int Partition(int left, int right) {
        int pivotValue = numbersToSort[right];
        int i = left - 1;

        for (int j = left; j < right; ++j) {
            if (numbersToSort[j] <= pivotValue) {
                i++;
                std::swap(numbersToSort[i], numbersToSort[j]);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                DrawNumbers(i,j);
                wxYield();
            }
        }

        std::swap(numbersToSort[i + 1], numbersToSort[right]);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        DrawNumbers(i+1,right);
        wxYield();
        return i + 1;
    }
    void OnQuickSort(wxCommandEvent& event) {
        QuickSort(0, numbersToSort.size() - 1);
    }

    void Merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> leftArray(n1);
        std::vector<int> rightArray(n2);

        for (int i = 0; i < n1; i++) {
            leftArray[i] = numbersToSort[left + i];
        }
        for (int i = 0; i < n2; i++) {
            rightArray[i] = numbersToSort[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                numbersToSort[k++] = leftArray[i++];
            }
            else {
                numbersToSort[k++] = rightArray[j++];
            }
        }

        while (i < n1) {
            numbersToSort[k++] = leftArray[i++];
        }

        while (j < n2) {
            numbersToSort[k++] = rightArray[j++];
        }
    }

    void MergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            MergeSort(left, mid);
            MergeSort(mid + 1, right);
            Merge(left, mid, right);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            DrawNumbers();
            wxYield();
        }
    }

    void OnMergeSort(wxCommandEvent& event) {
        MergeSort(0, numbersToSort.size() - 1);
    }
    void RadixSort() {
        int maxElement = *std::max_element(numbersToSort.begin(), numbersToSort.end());

        for (int exp = 1; maxElement / exp > 0; exp *= 10) {
            CountingSort(exp);
        }
    }

    void CountingSort(int exp) {
        int n = numbersToSort.size();
        std::vector<int> output(n);
        std::vector<int> count(10, 0);

        for (int i = 0; i < n; ++i) {
            count[(numbersToSort[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            output[count[(numbersToSort[i] / exp) % 10] - 1] = numbersToSort[i];
            count[(numbersToSort[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; ++i) {
            numbersToSort[i] = output[i];
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Adjust the delay as needed
            DrawNumbers();
            wxYield();
        }
    }

    void OnRadixSort(wxCommandEvent& event) {
        RadixSort();
    }
    
    void InsertionSort() {
        int n = numbersToSort.size();
        for (int i = 1; i < n; ++i) {
            int key = numbersToSort[i];
            int j = i - 1;

            while (j >= 0 && numbersToSort[j] > key) {
                numbersToSort[j + 1] = numbersToSort[j];
                j--;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                DrawNumbers();
                wxYield();
            }

            numbersToSort[j + 1] = key;
        }
    }

    void OnInsertionSort(wxCommandEvent& event) {
        std::thread sortingThread(&SortVisualizerFrame::InsertionSort, this);
        sortingThread.detach();
    }

    void SelectionSort() {
        int n = numbersToSort.size();

        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (numbersToSort[j] < numbersToSort[minIndex]) {
                    minIndex = j;
                }
            }
            std::swap(numbersToSort[i], numbersToSort[minIndex]);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            DrawNumbers();
            wxYield();
        }
    }

    void OnSelectionSort(wxCommandEvent& event) {
        std::thread sortingThread(&SortVisualizerFrame::SelectionSort, this);
        sortingThread.detach();
    }

    void Heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && numbersToSort[left] > numbersToSort[largest])
            largest = left;

        if (right < n && numbersToSort[right] > numbersToSort[largest])
            largest = right;

        if (largest != i) {
            std::swap(numbersToSort[i], numbersToSort[largest]);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            DrawNumbers();
            wxYield();
            Heapify(n, largest);
        }
    }

    // Add the HeapSort function to your SortVisualizerFrame class
    void HeapSort() {
        int n = numbersToSort.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(n, i);

        for (int i = n - 1; i >= 0; i--) {
            std::swap(numbersToSort[0], numbersToSort[i]);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            DrawNumbers();
            wxYield();
            Heapify(i, 0);
        }
    }

    // Add the event handler for the Heap Sort button
    void OnHeapSort(wxCommandEvent& event) {
        HeapSort();
    }

    void ShellSort() {
        int n = numbersToSort.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = numbersToSort[i];
                int j;
                for (j = i; j >= gap && numbersToSort[j - gap] > temp; j -= gap) {
                    numbersToSort[j] = numbersToSort[j - gap];
                }
                numbersToSort[j] = temp;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                DrawNumbers();
                wxYield();
            }
        }
    }

    void OnShellSort(wxCommandEvent& event) {
        ShellSort();
    }

    void CombSort() {
        int gap = numbersToSort.size();
        bool swapped = true;
        double shrinkFactor = 1.3;

        while (gap > 1 || swapped) {
            gap = static_cast<int>(gap / shrinkFactor);

            if (gap < 1) {
                gap = 1;
            }

            swapped = false;
            for (int i = 0; i < numbersToSort.size() - gap; ++i) {
                if (numbersToSort[i] > numbersToSort[i + gap]) {
                    std::swap(numbersToSort[i], numbersToSort[i + gap]);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    DrawNumbers();
                    wxYield();
                    swapped = true;
                }
            }
        }
    }

    void OnCombSort(wxCommandEvent& event) {
        std::thread sortingThread(&SortVisualizerFrame::CombSort, this);
        sortingThread.detach();
    }


    void CycleSort() {
        int n = numbersToSort.size();

        for (int cycleStart = 0; cycleStart < n - 1; ++cycleStart) {
            int item = numbersToSort[cycleStart];
            int pos = cycleStart;

            for (int i = cycleStart + 1; i < n; ++i) {
                if (numbersToSort[i] < item) {
                    pos++;
                }
            }

            if (pos == cycleStart) {
                continue;
            }

            while (item == numbersToSort[pos]) {
                pos++;
            }

            std::swap(item, numbersToSort[pos]);

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            DrawNumbers();
            wxYield();

            while (pos != cycleStart) {
                pos = cycleStart;

                for (int i = cycleStart + 1; i < n; ++i) {
                    if (numbersToSort[i] < item) {
                        pos++;
                    }
                }

                while (item == numbersToSort[pos]) {
                    pos++;
                }

                std::swap(item, numbersToSort[pos]);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                DrawNumbers();
                wxYield();
            }
        }
    }


    void OnCycleSort(wxCommandEvent& event) {
        CycleSort();
    }

    void CocktailShakerSort();
    void OnCocktailShakerSort();
};



class SortVisualizerApp : public wxApp {
public:
    virtual bool OnInit() {
        SortVisualizerFrame* frame = new SortVisualizerFrame("Sorting Visualizer", wxPoint(50, 50), wxSize(900, 500));
        frame->SetMinSize(wxSize(1100, 500));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(SortVisualizerApp);
