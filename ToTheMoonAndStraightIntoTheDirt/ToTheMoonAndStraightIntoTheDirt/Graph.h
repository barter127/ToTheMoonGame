#pragma once

// Graph drawing.
extern float lastPrice; 
extern int lastGraphHeight; 
extern const int GRAPH_TOP; 
extern const int GRAPH_BOTTOM; 
extern int moneyMultiplier;

extern int rngWeight;

// from main
extern float assetPrice;

// Prints graph data all at once. Allows for more seamless visual updates.
void DrawGraphBuffer();

// Draws the vertical line and numerical values to the left of the graph.
void DrawYAxisLabel(int graphHeight);

// Check which symbol to draw depending if the market went up or down.
void DrawGraphLine(short fluctuation);

// literally just prints a space. Used to avoid iostream in a header.
void DrawWhiteSpace();

// New line. Avoids iostream in the header.
void NewLine(); // Might be a bit excessive.

// Random number between
float RandomiseFluctuation(int &weight);

float RandomRange(int lowest, int highest);

// Var between (0 and Hi) or (Lo and 0) is weight times more likely
float WeightedRNG(int Lo, int Hi, int weight);



// Prints stock graph (parameter) to console.
template <size_t rows, size_t cols>
void BufferGraph(short (&marketGraph)[rows][cols])
{
    // Loop for height.
    for (int gHeight = GRAPH_TOP; gHeight > 0; gHeight--)
    {
        // Draw left side of graph.
        DrawYAxisLabel(gHeight);

        // Loop for graph width.
        for (int gWidth = 0; gWidth < rows; gWidth++)
        {
            // If there isn't a value at this position.
            if (gHeight != marketGraph[gWidth][0]) DrawWhiteSpace();

            else
            {
                // Draw corresponding output.
                DrawGraphLine(marketGraph[gWidth][1]);
            }
        }

        NewLine();
    }
}

template <size_t rows, size_t cols>
void ShiftMarketArray(short (&marketGraph)[rows][cols])
{
    // Move all fields over by one.
    for (int i = 0; i < rows - 1; i++) // Loop 1 less than length.
    {
        marketGraph[i][0] = marketGraph[i + 1][0];
        marketGraph[i][1] = marketGraph[i + 1][1];
    }
}

// Updates the markertArray so the last element of the array is new
// Shifts the rest of the array left and discards the first value.
template <size_t rows, size_t cols>
void UpdateMarket(short (&marketGraph)[rows][cols])
{
    ShiftMarketArray(marketGraph);

    float fluctuation = RandomiseFluctuation(rngWeight);
    assetPrice += fluctuation;

    int graphHeight = assetPrice / moneyMultiplier;
    int graphChange = graphHeight - lastGraphHeight;
    marketGraph[rows - 1][1] = graphChange;

    // Check to align graph lines (quirk of text based).
    if (graphChange == 1)
    {
        marketGraph[rows - 1][0] = graphHeight - 1;
    }
    else
    {
        marketGraph[rows - 1][0] = graphHeight;
    }

    // MAYBE IMPLEMENT PROPERLY
    //if (assetPrice > GRAPH_TOP * moneyMultiplier)
    //{
    //    moneyMultiplier *= 2;
    //}
    //else if (assetPrice > GRAPH_TOP * moneyMultiplier / 2)
    //{
    //    moneyMultiplier /= 2;
    //}


    lastGraphHeight = graphHeight;
}

// Initalise Graph by running update market for the amount of rows
template <size_t rows, size_t cols>
void IntialiseGraph(short (&marketGraph)[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        UpdateMarket(marketGraph);
    }
}