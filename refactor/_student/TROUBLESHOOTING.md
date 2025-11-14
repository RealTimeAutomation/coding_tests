# Troubleshooting Guide

## Permission Errors in WSL

If you encounter "Operation not permitted" errors when running `make test` or `cmake`, this is often due to Windows filesystem permissions in WSL.

### Solution 1: Use Linux Filesystem (Recommended)

Copy the project to a Linux filesystem instead of `/mnt/c/`:

```bash
# Copy to Linux filesystem
cp -r /mnt/c/RTA/coding_tests ~/coding_tests
cd ~/coding_tests/refactor/_student
make test
```

### Solution 2: Fix Permissions

If you must use `/mnt/c/`, try fixing permissions:

```bash
cd /mnt/c/RTA/coding_tests/refactor/_student
chmod -R 755 .
rm -rf build
make test
```

### Solution 3: Run as Different User

If you're in WSL, ensure you're running as your user (not root):

```bash
# Check current user
whoami

# If needed, fix ownership
sudo chown -R $USER:$USER /mnt/c/RTA/coding_tests
```

### Solution 4: Use WSL2 with Proper Mount Options

If using WSL2, you can remount with proper permissions:

```bash
# Add to /etc/wsl.conf (requires sudo)
[automount]
options = "metadata,umask=22,fmask=11"
```

Then restart WSL.

### Solution 5: Build in Temporary Directory

Build in a Linux filesystem temp directory:

```bash
cd /mnt/c/RTA/coding_tests/refactor/_student
mkdir -p /tmp/coding_tests_build
cd /tmp/coding_tests_build
cmake /mnt/c/RTA/coding_tests/refactor/_student
make
```

## Other Common Issues

### CMake Not Found

```bash
# Install CMake
sudo apt-get update
sudo apt-get install cmake build-essential
```

### Make Not Found

```bash
# Install build tools
sudo apt-get install build-essential
```

### Missing Dependencies

```bash
# Install all build dependencies
sudo apt-get update
sudo apt-get install build-essential cmake gcc make
```

