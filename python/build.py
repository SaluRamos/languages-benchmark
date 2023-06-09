from setuptools import setup, Extension

def main():
    setup(name="fputs",
          version="1.0.0",
          description="Python interface for the fputs C library function",
          author="SaluRamos",
          author_email="saluc.ramos@outlook.om",
          ext_modules=[Extension("fputs", ["mainpy.c"])])

if __name__ == "__main__":
    main()