from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lower, upper, length, split

class SparkUtils:
    def __init__(self, app_name="SparkApp"):
        self.spark = SparkSession.builder.appName(app_name).getOrCreate()

    # Basic Math Operations
    def basic_math(self):
        df = self.spark.createDataFrame([(1,), (2,), (3,), (4,)], ["num"])
        return df.select(
            col("num"),
            (col("num") + 10).alias("plus_10"),
            (col("num") * 2).alias("times_2"),
            (col("num") ** 2).alias("square")
        )

    # Array Operations
    def array_ops(self):
        df = self.spark.createDataFrame([([1, 2, 3],), ([4, 5],)], ["numbers"])
        return df.selectExpr("numbers", "size(numbers) as length", "numbers[0] as first_element")

    # String Operations
    def string_ops(self):
        data = [("hello world",), ("Spark is great",)]
        df = self.spark.createDataFrame(data, ["text"])
        return df.select(
            col("text"),
            lower(col("text")).alias("lower"),
            upper(col("text")).alias("upper"),
            length(col("text")).alias("length"),
            split(col("text"), " ").alias("words")
        )

    # Load & Preprocess Data
    def load_and_preprocess(self, path):
        df = self.spark.read.option("header", True).csv(path, inferSchema=True)
        print("Original Schema:")
        df.printSchema()

        # Sample preprocessing: drop nulls, convert string columns to lowercase
        df_clean = df.dropna()
        for col_name, dtype in df_clean.dtypes:
            if dtype == 'string':
                df_clean = df_clean.withColumn(col_name, lower(col(col_name)))
        return df_clean
