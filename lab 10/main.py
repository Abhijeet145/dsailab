from spark_utils import SparkUtils

def run():
    spark_tool = SparkUtils("SparkDemo")

    print("### Basic Math Operations ###")
    math_df = spark_tool.basic_math()
    math_df.show()

    print("### Array Operations ###")
    array_df = spark_tool.array_ops()
    array_df.show()

    print("### String Operations ###")
    string_df = spark_tool.string_ops()
    string_df.show()

    # Change the path below to point to your CSV data file.
    data_path = "MidSem_Dataset_AssociationRuleMining_Market_Basket_Optimisation.csv"
    print("### Loading and Preprocessing Data ###")
    try:
        cleaned_df = spark_tool.load_and_preprocess(data_path)
        cleaned_df.show()
    except Exception as e:
        print("Error loading data. Make sure the file exists and is accessible.")
        print(e)

if __name__ == "__main__":
    run()
