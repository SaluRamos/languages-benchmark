from setuptools import setup, Extension

def main():
    setup(name="salubenchmark", #just a name
          version="1.0.0",
          description="Python interface for the fputs C library function",
          author="SaluRamos",
          author_email="saluc.ramos@outlook.om",
          ext_modules=[Extension("salubenchmark", ["salubenchmark.c"])])

if __name__ == "__main__":
    main()