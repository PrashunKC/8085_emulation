# Branch Protection Rules

This document outlines the recommended branch protection rules for the 8085 Emulator repository to maintain code quality and prevent accidental changes to critical branches.

> **Quick Setup**: See [.github/BRANCH_PROTECTION_SETUP.md](.github/BRANCH_PROTECTION_SETUP.md) for step-by-step instructions to configure these rules.

## Recommended Settings for Main Branch

### 1. Protect Against Force Push
**Setting:** Prevent force pushes to the `main` branch

**Why:** Force pushing rewrites git history, which can cause:
- Loss of commit history
- Confusion for collaborators
- Difficulty tracking changes
- Potential data loss

**How to Enable:**
1. Go to repository Settings → Branches
2. Add branch protection rule for `main`
3. Check ✅ "Do not allow force pushes"

### 2. Protect Against Branch Deletion
**Setting:** Prevent deletion of the `main` branch

**Why:** Deleting the main branch would:
- Remove the entire project history
- Break all open pull requests
- Disrupt collaborators' work
- Potentially cause data loss

**How to Enable:**
1. Go to repository Settings → Branches
2. Add branch protection rule for `main`
3. Check ✅ "Do not allow deletions"

### 3. Require Status Checks Before Merging
**Setting:** Require status checks to pass before merging

**Why:** Ensures that:
- Code builds successfully
- Tests pass
- Code quality standards are met
- No breaking changes are introduced

**How to Enable:**
1. Go to repository Settings → Branches
2. Add branch protection rule for `main`
3. Check ✅ "Require status checks to pass before merging"
4. Check ✅ "Require branches to be up to date before merging"
5. Select required status checks:
   - `build` (if CI/CD workflow exists)
   - `test` (if test workflow exists)
   - `lint` (if linting workflow exists)

### 4. Additional Recommended Settings

#### Require Pull Request Reviews
- Check ✅ "Require a pull request before merging"
- Set "Required number of approvals before merging" to at least 1
- Check ✅ "Dismiss stale pull request approvals when new commits are pushed"

**Why:** Ensures code review happens before changes reach main branch

#### Require Conversation Resolution
- Check ✅ "Require conversation resolution before merging"

**Why:** Ensures all feedback is addressed before merging

#### Include Administrators
- Check ✅ "Include administrators"

**Why:** Ensures even repository administrators follow the same rules, preventing accidental force pushes or deletions

## Quick Setup Guide

To apply all recommended protections to the `main` branch:

1. Navigate to: `https://github.com/PrashunKC/8085_emulation/settings/branches`
2. Click "Add branch protection rule"
3. Enter branch name pattern: `main`
4. Enable the following settings:
   - ✅ Require a pull request before merging
     - ✅ Require approvals (1)
     - ✅ Dismiss stale pull request approvals when new commits are pushed
   - ✅ Require status checks to pass before merging (if CI/CD is set up)
     - ✅ Require branches to be up to date before merging
   - ✅ Require conversation resolution before merging
   - ✅ Do not allow bypassing the above settings
   - ✅ Do not allow force pushes
   - ✅ Do not allow deletions
5. Click "Create" or "Save changes"

## Current Repository Status

As of the creation of this document:
- Repository: PrashunKC/8085_emulation
- Main branch: `main`
- Programming languages: C++ with Qt5
- Build system: Make/CMake

## CI/CD Integration (Optional)

For automated status checks, consider setting up GitHub Actions workflows:
- Build verification
- Code quality checks
- Automated testing

See `.github/workflows/` directory for example workflow configurations.

## Notes

- These settings require repository admin permissions to configure
- Once enabled, all contributors (including admins) must follow these rules
- Settings can be adjusted later based on team workflow needs
- For questions or changes, contact the repository owner

## References

- [GitHub Branch Protection Documentation](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches)
- [Managing Branch Protection Rules](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/managing-a-branch-protection-rule)
