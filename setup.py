from setuptools import setup

setup(name='ardupy_gui',
        verison='0.1',
        description='Simple Arduino written in C++ with CEFPython interface',
        url='',
        author='Matthew Westphall',
        author_email='w.matthew.he@gmail.com',
        packages=['ardupy_gui'],
        install_requires=[
            'cefpython3',
            'pySerial'
        ]
)
